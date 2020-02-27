#include <patrolstrategy.h>

PatrolStrategy::PatrolStrategy(int left, int right) {
    leftBound = left;
    rightBound = right;
}

void PatrolStrategy::move(int& velx, int& vely, int posx, int posy, int speed,
    int playerx, int playery) {
    if (posx <= leftBound) {
        velx = speed;
    } else if (posx >= rightBound) {
        velx = speed * -1;
    }
}
