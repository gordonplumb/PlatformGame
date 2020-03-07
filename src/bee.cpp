#include <bee.h>
#include <observer.h>
#include <movementstrategy.h>

Bee::Bee(int x, int y, MovementStrategy* strategy, Observer* observer): 
    AbstractEnemy(WIDTH, HEIGHT, MAX_SPEED, x, y, MAX_HP, DAMAGE, strategy,
        observer) {}

Bee::~Bee() {}

void Bee::move(int playerx, int playery) {
    strategy->move(xVel, yVel, xPos, yPos, maxSpeed, playerx, playery);

    xPos += xVel;
    yPos += yVel;

    if (xVel != 0) {
        forward = !(xVel > 0);
    }
}
