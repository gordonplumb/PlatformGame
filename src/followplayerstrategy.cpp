#include <followplayerstrategy.h>

FollowPlayerStrategy::FollowPlayerStrategy(bool flying) {
    this->flying = flying;
}

FollowPlayerStrategy::~FollowPlayerStrategy() {}

void FollowPlayerStrategy::move(int& velx, int& vely, int posx, int posy,
    int speed, int playerx, int playery) {

    if (playerx <= posx) {
        velx = speed * -1;
    } else if (playerx >= posx) {
        velx = speed;
    }

    if (flying) {
        if (playery <= posy) {
            vely = speed * -1;
        } else {
            vely = speed;
        }
    }
}