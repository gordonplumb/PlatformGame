#include <gameconstants.h>
#include <player.h>
#include <laser.h>
#include <observer.h>

Player::Player(Observer* observer):
    AbstractEntity(PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_MAX_SPEED,
                   0, 0, 10, 0) {
    addObserver(observer);
}

Player::~Player() {}

void Player::move(uint32_t time) {
    applyGravity();
    
    // remove invincibility once timer is up
    if (invincible && time > invincibilityTimer + 3 * 1000) {
        invincible = false;
    }

    mPosX += mVelX;
    mPosY += mVelY;

    // determine direction to face
    if (mVelX - xRecoil != 0) {
        mForward = mVelX - xRecoil > 0;
    }

    mHitBox.x = mPosX;
    mHitBox.y = mPosY;

    removeRecoil();
}

void Player::notifyObservers() {
    SDL_Point* centre = new SDL_Point {mHitBox.x + mWidth / 2,
                                       mHitBox.y + mHeight / 2};
    for (Observer* observer : observers) {
        observer->notify(mHP, mPosX, mPosY, mForward, mCrouching, mLookingUp,
                         mVelX != 0, 0, centre);
    }
}

void Player::reset() {
    mPosX = 0;
    mPosY = 0;
    mHitBox.x = 0;
    mHitBox.y = 0;
    mVelX = 0;
    mVelY = 0;
    mLookingUp = false;
    mCrouching = false;
}

Laser* Player::fireLaser() {
    bool horizontal, vertical;
    int x, y;
    int xModifier = mForward ? 1 : -1;
    int yModifier = mLookingUp ? -1 : 1;
    if (mCrouching) {
        horizontal = true;
        x = mHitBox.x + (mForward ? 31 : -10);
        y = mHitBox.y + 52;
    } else if (mLookingUp && mVelX == 0) {
        vertical = true;
        x = mHitBox.x + (mForward ? 35 : 10);
        y = mHitBox.y + 15;
    } else {
        horizontal = true;
        vertical = mLookingUp;
        x = mHitBox.x + (mForward ? 37 : -17);
        y = mHitBox.y + 38;
    }

    return new Laser(x, y, horizontal, vertical, xModifier, yModifier, 1);
}
