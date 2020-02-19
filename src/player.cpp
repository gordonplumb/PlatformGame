#include <gameconstants.h>
#include <player.h>
#include <laser.h>
#include <observer.h>

Player::Player(Observer* observer):
    AbstractEntity(PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_MAX_SPEED,
                   100, 200, 5) {
    addObserver(observer);
}

Player::~Player() {}

void Player::move(int top, int bot, int left, int right) {
    applyGravity();
    mPosX += mVelX;
    if ((mPosX < left) || (mPosX + PLAYER_WIDTH > right)) {
        mPosX -= mVelX;
    }

    // determine direction to face
    if (mVelX != 0) {
        mForward = mVelX > 0;
    }

    mPosY += mVelY;
    if ((mPosY < top) || (mPosY + PLAYER_HEIGHT > bot)) {
        mPosY -= mVelY;
    }
    mHitBox.x = mPosX;
    mHitBox.y = mPosY;
}

void Player::notifyObservers() {
    SDL_Point* centre = new SDL_Point {mHitBox.x + mWidth / 2,
                                       mHitBox.y + mHeight / 2};
    observer->notify(mPosX, mPosY, mForward, mCrouching, mLookingUp, mVelX != 0,
                     0, centre);
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

    return new Laser(x, y, horizontal, vertical, xModifier, yModifier);
}
