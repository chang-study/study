#ifndef MALLARD_DUCK_H
#define MALLARD_DUCK_H

#include "Duck.h"
#include "Quack.h"
#include "FlyWithWings.h"
#include <iostream>

class MallardDuck : public Duck {
    public:
        MallardDuck();
        void display() const override {
            std::cout << "I'm a mallard duck!\n";
        }
};

inline
MallardDuck::MallardDuck() {
    quackBehavior = std::make_unique<Quack>();
    flyBehavior = std::make_unique<FlyWithWings>();
}

#endif /* ifndef MALLARD_DUCK_H */