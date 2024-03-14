#include "Duck.h"
#include "MallardDuck.h"
#include "ModelDuck.h"
#include "FlyRocketPowered.h"
#include "MuteDuck.h"
#include <memory>

int main() {
    using DuckPtr = std::unique_ptr<Duck>; // type alias
    DuckPtr mallard = std::make_unique<MallardDuck>();
    mallard->performQuack();
    mallard->performFly();

    DuckPtr model = std::make_unique<ModelDuck>();
    model->performQuack();
    model->setFlyBehavior(std::make_unique<FlyRocketPowered>());
    model->performFly();

    DuckPtr muteDuck = std::make_unique<MuteDuck>();
    muteDuck->performQuack();
    muteDuck->performFly();
    muteDuck->display();

    return 0;
}