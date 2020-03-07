#ifndef PATROLSTRATEGY_H
#define PATROLSTRATEGY_H

#include <movementstrategy.h>

class PatrolStrategy: public MovementStrategy {
    int leftBound;
    int rightBound;

    public:
    PatrolStrategy(int left, int right);
    ~PatrolStrategy();
    void move(int& xVel, int& yVel, int xPos, int yPos, int speed, int playerX,
        int playerY) override;
};

#endif