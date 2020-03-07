#include <followplayerstrategy.h>

FollowPlayerStrategy::FollowPlayerStrategy(bool flying) {
    this->flying = flying;
}

FollowPlayerStrategy::~FollowPlayerStrategy() {}

void FollowPlayerStrategy::move(int& xVel, int& yVel, int xPos, int yPos,
    int speed, int playerX, int playerY) {

    if (playerX < xPos) {
        xVel = speed * -1;
    } else if (playerX > xPos) {
        xVel = speed;
    } else {
        xVel = 0;
    }

    if (flying) {
        if (playerY < yPos) {
            yVel = speed * -1;
        } else if (playerY > yPos) {
            yVel = speed;
        } else {
            yVel = 0;
        }
    }
}