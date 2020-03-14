#ifndef PATROLSTRATEGY_H
#define PATROLSTRATEGY_H

#include <movementstrategy.h>

class PatrolStrategy: public MovementStrategy {
    bool vertical;
    int minBound;
    int maxBound;

    public:
    PatrolStrategy(bool vertical, int min, int max);
    ~PatrolStrategy();

    void move(int& xVel, int& yVel, int xPos, int yPos, int speed, int playerX,
        int playerY) override;
};

#endif