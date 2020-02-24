#include <laser.h>
#include <gameconstants.h>
#include <observer.h>

Laser::Laser(int x, int y, bool horizontal, bool vertical, int xModifier,
             int yModifier):
    AbstractEntity {LASER_WIDTH, LASER_HEIGHT, LASER_MAX_SPEED, x, y, 1} {
    id = LASER_ID;
    centre = new SDL_Point {mWidth / 2, mHeight / 2};
    if (horizontal && vertical) {
        // TODO: change this, also hitbox needs to be modified for diagonal
        mVelX = 7 * xModifier;
        mVelY = 7 * yModifier;
        angle = 45 * xModifier * -1;
    } else if (horizontal) {
        mVelX = LASER_MAX_SPEED * xModifier;
        mVelY = 0;
        angle = 0;
    } else {
        mVelX = 0;
        mVelY = LASER_MAX_SPEED * yModifier;
        angle = 90;
    }
}

Laser::~Laser() {}

void Laser::move(uint32_t time) {
    mPosX += mVelX;
    mPosY += mVelY;
    mHitBox.x = mPosX;
    mHitBox.y = mPosY;
}

void Laser::notifyObservers() {
    for (Observer* observer : observers) {
       observer->notify(mHP, mPosX, mPosY, mForward, mCrouching, mLookingUp,
                     mVelX != 0, angle, centre); 
    }
}
