#ifndef SQUACK_H
#define SQUACK_H

#include "QuackBehavior.h"
#include <iostream>

class Squack : public QuackBehavior {
    public:
        void quack() override {
            std::cout << "squack\n";
        }
};

#endif /* ifndef SQUACK_H */