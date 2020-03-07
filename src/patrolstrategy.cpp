#include <patrolstrategy.h>

PatrolStrategy::PatrolStrategy(int left, int right): leftBound(left),
    rightBound(right) {}

PatrolStrategy::~PatrolStrategy() {}

void PatrolStrategy::move(int& xVel, int& yVel, int xPos, int yPos, int speed,
    int playerX, int playerY) {
    if (xPos <= leftBound) {
        xVel = speed;
    } else if (xPos >= rightBound) {
        xVel = speed * -1;
    }
}
