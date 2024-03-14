#ifndef FLY_NOWAY_H
#define FLY_NOWAY_H

#include "FlyBehavior.h"
#include <iostream>

class FlyNoWay : public FlyBehavior {
    public:
        void fly() override {
            std::cout << "can't flying\n";
        }
};

#endif /* ifndef FLY_NOWAY_H */