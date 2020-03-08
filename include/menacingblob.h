#ifndef MENACINGBLOB_H
#define MENACINGBLOB_H

#include <memory>
#include <abstractenemy.h>

class Observer;

class MenacingBlob: public AbstractEnemy {
    public:
    static const int WIDTH = 30;
    static const int HEIGHT = 30;
    static const int MAX_SPEED = 2;
    static const int MAX_HP = 1;
    static const int DAMAGE = 1;

    MenacingBlob(int x, int y, std::unique_ptr<MovementStrategy>& strategy,
        std::unique_ptr<Observer> observer);
    ~MenacingBlob();
};

#endif