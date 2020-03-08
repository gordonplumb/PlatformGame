#include <memory>
#include <abstractenemy.h>
#include <movementstrategy.h>
#include <observer.h>

using namespace std;

AbstractEnemy::AbstractEnemy(int width, int height, int maxSpeed, int x, int y,
    int totalHP, int damage, unique_ptr<MovementStrategy> strategy,
    unique_ptr<Observer> observer): 
    AbstractEntity(width, height, maxSpeed, x, y, totalHP, damage),
    strategy(std::move(strategy)) {
    addObserver(std::move(observer));
}

AbstractEnemy::~AbstractEnemy() {}

void AbstractEnemy::move(int playerX, int playerY) {
    applyGravity();
    strategy->move(xVel, yVel, xPos, yPos, maxSpeed, playerX, playerY);

    xPos += xVel;
    yPos += yVel;

    if (xVel != 0) {
        forward = !(xVel > 0);
    }
}
