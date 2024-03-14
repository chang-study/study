#ifndef FLY_WITH_WINGS_H
#define FLY_WITH_WINGS_H

#include "FlyBehavior.h"
#include <iostream>

class FlyWithWings : public FlyBehavior {
    public:
        void fly() override {
            std::cout << "flying\n";
        }
};

#endif /* ifndef FLY_WITH_WINGS_H */