#ifndef MODEL_DUCK_H
#define MODEL_DUCK_H

#include "Duck.h"
#include "Quack.h"
#include "FlyNoWay.h"
#include <iostream>

class ModelDuck : public Duck {
    public:
        ModelDuck();
        void display() const override {
            std::cout << "I'm a model duck!\n";
        }
};

inline
ModelDuck::ModelDuck() {
    quackBehavior = std::make_unique<Quack>();
    flyBehavior = std::make_unique<FlyNoWay>();
}

#endif /* ifndef MODEL_DUCK_H */