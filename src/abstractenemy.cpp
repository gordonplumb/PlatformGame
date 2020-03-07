#include <abstractenemy.h>
#include <movementstrategy.h>
#include <observer.h>

AbstractEnemy::AbstractEnemy(int width, int height, int maxSpeed, int x, int y,
    int totalHP, int damage, MovementStrategy* strategy, Observer* observer): 
    AbstractEntity(width, height, maxSpeed, x, y, totalHP, damage),
    strategy(strategy) {
    addObserver(observer);
}

AbstractEnemy::~AbstractEnemy() {}

void AbstractEnemy::move(int playerx, int playery) {
    applyGravity();
    strategy->move(xVel, yVel, xPos, yPos, maxSpeed, playerx, playery);

    xPos += xVel;
    yPos += yVel;

    if (xVel != 0) {
        forward = !(xVel > 0);
    }
}
