#ifndef QUACK_MUTE_H
#define QUACK_MUTE_H

#include "QuackBehavior.h"
#include <iostream>

class QuackMute : public QuackBehavior {
    public:
        void quack() override {
            std::cout << "Silence\n";
        }
};

#endif /* ifndef QUACK_MUTE_H */