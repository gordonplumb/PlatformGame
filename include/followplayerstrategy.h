#ifndef _FOLLOW_PLAYER_STRATEGY_H_
#define _FOLLOW_PLAYER_STRATEGY_H_

#include <movementstrategy.h>

class FollowPlayerStrategy: public MovementStrategy {
    bool flying;

    public:
    FollowPlayerStrategy(bool flying);
    ~FollowPlayerStrategy();

    void move(int& velx, int& vely, int posx, int posy, int speed,
        int playerx, int playery) override;
};

#endif