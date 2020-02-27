#include <bee.h>
#include <observer.h>
#include <movementstrategy.h>

Bee::Bee(int x, int y, MovementStrategy* strategy, Observer* observer): 
    AbstractEnemy(WIDTH, HEIGHT, MAX_SPEED, x, y, MAX_HP, DAMAGE, strategy,
        observer) {}

Bee::~Bee() {}

void Bee::move(int playerx, int playery) {
    strategy->move(mVelX, mVelY, mPosX, mPosY, mMaxSpeed, playerx, playery);

    mPosX += mVelX;
    mPosY += mVelY;

    if (mVelX != 0) {
        mForward = !(mVelX > 0);
    }
    
    mHitBox.x = mPosX;
    mHitBox.y = mPosY;
    removeRecoil();
}
