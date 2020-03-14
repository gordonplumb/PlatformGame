#include <patrolstrategy.h>

PatrolStrategy::PatrolStrategy(bool vertical, int min, int max): 
    vertical(vertical), minBound(min), maxBound(max) {}

PatrolStrategy::~PatrolStrategy() {}

void PatrolStrategy::move(int& xVel, int& yVel, int xPos, int yPos, int speed,
    int playerX, int playerY) {
    if (vertical) {
        if (yPos <= minBound || yVel == 0) {
        yVel = speed;
        } else if (yPos >= maxBound) {
            yVel = speed * -1;
        }
    } else {
        if (xPos <= minBound || xVel == 0) {
            xVel = speed;
        } else if (xPos >= maxBound) {
            xVel = speed * -1;
        }
    }    
}
