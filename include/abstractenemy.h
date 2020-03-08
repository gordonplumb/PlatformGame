#ifndef ABSTRACTENEMY_H
#define ABSTRACTENEMY_H

#include <memory>
#include <abstractentity.h>

class Observer;
class MovementStrategy;

class AbstractEnemy: public AbstractEntity {
    protected:
    std::unique_ptr<MovementStrategy> strategy;

    public:
    AbstractEnemy(int width, int height, int maxSpeed, int x, int y,
        int totalHP, int damage, std::unique_ptr<MovementStrategy> strategy,
        std::unique_ptr<Observer> observer);
    ~AbstractEnemy();

    virtual void move(int playerX, int playerY);
};

#endif