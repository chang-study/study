from pwn import *

# 1. argc is 100
# 2. argv["A"] is \x00
# 3. argv["B"] is \x20\x0a\x0d
argv = ["A" for _ in range(100)]
argv[ord("A")] = "\x00"
argv[ord("B")] = "\x20\x0a\x0d"
argv[ord("C")] = "66666"

# 5. write \x00\x0a\x02\xff as STDERR
with open("./stderr", "w") as f:
    f.write("\x00\x0a\x02\xff")

# 6. \xde\xad\xbe\xef env is \xca\xfe\xba\xbe
env = {"\xde\xad\xbe\xef": "\xca\xfe\xba\xbe"}

# 7. read \x00\x00\x00\x00 in file named \x0a
with open("./\x0a", "w") as f:
    f.write("\x00\x00\x00\x00")

target1 = process(executable="/home/input2/input", argv=argv, stderr=open("./stderr"), env=env)
# 4. write \x00\x0a\x02\xff as STDIN
target1.sendline("\x00\x0a\x02\xff")

# 8. read \xde\xad\xbe\xef in socket argv["C"] port
target2 = remote("localhost", 66666)
target2.send("\xde\xad\xbe\xef")

target1.interactive()