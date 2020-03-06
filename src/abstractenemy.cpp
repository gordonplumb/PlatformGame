#include <abstractenemy.h>
#include <movementstrategy.h>
#include <observer.h>

AbstractEnemy::AbstractEnemy(int width, int height, int maxSpeed, int x, int y,
    int totalHP, int damage, MovementStrategy* strategy, Observer* observer): 
    AbstractEntity(width, height, maxSpeed, x, y, totalHP, damage) {
    this->strategy = strategy;
    addObserver(observer);
}

AbstractEnemy::~AbstractEnemy() {}

void AbstractEnemy::move(int playerx, int playery) {
    applyGravity();
    strategy->move(mVelX, mVelY, mPosX, mPosY, mMaxSpeed, playerx, playery);

    mPosX += mVelX;
    mPosY += mVelY;

    if (mVelX != 0) {
        mForward = !(mVelX > 0);
    }
    
    mHitBox.x = mPosX;
    mHitBox.y = mPosY;
}
