#ifndef QUACK_BEHAVIOR_H
#define QUACK_BEHAVIOR_H

class QuackBehavior {
    public:
        virtual ~QuackBehavior() = default;
        virtual void quack() = 0;   
};

#endif /* ifndef QUACK_BEHAVIOR_H */