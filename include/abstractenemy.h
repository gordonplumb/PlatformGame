#ifndef ABSTRACTENEMY_H
#define ABSTRACTENEMY_H

#include <abstractentity.h>

class Observer;
class MovementStrategy;

class AbstractEnemy: public AbstractEntity {
    protected:
    MovementStrategy* strategy;

    public:
    AbstractEnemy(int width, int height, int maxSpeed, int x, int y,
        int totalHP, int damage, MovementStrategy* strategy,
        Observer* observer);
    ~AbstractEnemy();

    virtual void move(int playerX, int playerY);
};

#endif