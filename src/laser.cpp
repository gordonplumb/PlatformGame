#include <memory>
#include <laser.h>
#include <observer.h>

using namespace std;

Laser::Laser(int x, int y, bool horizontal, bool vertical, int xModifier,
             int yModifier, int damage, unique_ptr<Observer> observer):
    AbstractEntity {LASER_WIDTH, LASER_HEIGHT, LASER_MAX_SPEED, x, y, 1,
        damage} {
    if (horizontal && vertical) {
        xVel = 7 * xModifier;
        yVel = 7 * yModifier;
        angle = 45 * xModifier * -1;
    } else if (horizontal) {
        xVel = LASER_MAX_SPEED * xModifier;
        yVel = 0;
        angle = 0;
    } else {
        xVel = 0;
        yVel = LASER_MAX_SPEED * yModifier;
        angle = 90;
    }
    addObserver(std::move(observer));
}

Laser::~Laser() {}

void Laser::move() {
    xPos += xVel;
    yPos += yVel;
}

void Laser::notifyObservers() {
    for (auto& observer : observers) {
        observer->notify(hitpoints, xPos, yPos, forward, crouching, lookingUp,
            xVel != 0, angle); 
    }
}
