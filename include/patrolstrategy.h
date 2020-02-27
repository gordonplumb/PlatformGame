#ifndef _PATROL_STRATEGY_
#define _PATROL_STRATEGY_

#include <movementstrategy.h>

class PatrolStrategy: public MovementStrategy {
    int leftBound;
    int rightBound;

    public:
    PatrolStrategy(int left, int right);
    void move(int& velx, int& vely, int posx, int posy, int speed, int playerx,
        int playery) override;
};

#endif