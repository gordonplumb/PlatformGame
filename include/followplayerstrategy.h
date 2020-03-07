#ifndef FOLLOWPLAYERSTRATEGY_H
#define FOLLOWPLAYERSTRATEGY_H

#include <movementstrategy.h>

class FollowPlayerStrategy: public MovementStrategy {
    bool flying;

    public:
    FollowPlayerStrategy(bool flying);
    ~FollowPlayerStrategy();

    void move(int& xVel, int& yVel, int xPos, int yPos, int speed,int playerX,
        int playerY) override;
};

#endif