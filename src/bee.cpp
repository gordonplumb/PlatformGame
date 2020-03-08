#include <memory>
#include <abstractenemy.h>
#include <bee.h>
#include <observer.h>
#include <movementstrategy.h>

using namespace std;

Bee::Bee(int x, int y, unique_ptr<MovementStrategy>& strategy,
    unique_ptr<Observer> observer): 
    AbstractEnemy(WIDTH, HEIGHT, MAX_SPEED, x, y, MAX_HP, DAMAGE,
        std::move(strategy), std::move(observer)) {}

Bee::~Bee() {}

void Bee::move(int playerX, int playerY) {
    strategy->move(xVel, yVel, xPos, yPos, maxSpeed, playerX, playerY);

    xPos += xVel;
    yPos += yVel;

    if (xVel != 0) {
        forward = !(xVel > 0);
    }
}
