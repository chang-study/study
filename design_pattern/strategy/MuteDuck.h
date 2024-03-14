#ifndef MUTE_DUCK_H
#define MUTE_DUCK_H

#include "Duck.h"
#include "MuteQuack.h"
#include "FlyWithWings.h"
#include <iostream>

class MuteDuck : public Duck {
    public:
        MuteDuck();
        void display() const override {
            std::cout << "I'm a mute duck!\n";
        }
};

inline
MuteDuck::MuteDuck() {
    quackBehavior = std::make_unique<MuteQuack>();
    flyBehavior = std::make_unique<FlyWithWings>();
}

#endif /* ifndef MUTE_DUCK_H */