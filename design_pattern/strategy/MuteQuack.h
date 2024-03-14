#ifndef MUTE_QUACK_H
#define MUTE_QUACK_H

#include "QuackBehavior.h"
#include <iostream>

class MuteQuack : public QuackBehavior {
    public:
        void quack() override {
            std::cout << "Silence\n";
        }
};

#endif /* ifndef MUTE_QUACK_H */