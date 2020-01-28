#include <SDL2/SDL.h>
#include <abstractentity.h>

AbstractEntity::AbstractEntity(int width, int height, int maxSpeed, int posX,
                               int posY, int totalHP, int maxWalkingFrame) {
    mWidth = width;
    mHeight = height;
    mMaxSpeed = maxSpeed;
    mPosX = posX;
    mPosY = posY;
    mTotalHP = totalHP;
    mHP = totalHP;
    mMaxWalkingFrame = maxWalkingFrame;
    mHitBox.w = width;
    mHitBox.h = height;
}

void AbstractEntity::changePosX(int amount) {
    mPosX += amount;
}

void AbstractEntity::changePosY(int amount) {
    mPosY += amount;
}

void AbstractEntity::applyGravity() {
    mVelY += 1;
}

bool AbstractEntity::canJump() {
    return mCanJump;
}

bool AbstractEntity::isCrouching() {
    return mCrouching;
}

void AbstractEntity::setJump(bool canJump) {
    mCanJump = canJump;
    if (canJump) {
        mVelY = 0;
    }
}

void AbstractEntity::setCrouch(bool crouching) {
    mCrouching = crouching;
}

void AbstractEntity::setLookingUp(bool lookingUp) {
    mLookingUp = lookingUp;
}

void AbstractEntity::reverse() {
    mPosX -= mVelX;
    mPosY -= mVelY;
}

int AbstractEntity::getVelX() {
    return mVelX;
}

int AbstractEntity::getVelY() {
    return mVelY;
}

int AbstractEntity::getTotalHP() {
    return mTotalHP;
}

int AbstractEntity::getHP() {
    return mHP;
}

void AbstractEntity::changeVelX(int velX) {
    mVelX += velX;
}

void AbstractEntity::changeVelY(int velY) {
    mVelY += velY;
}

void AbstractEntity::changeHP(int amount) {
    mHP += amount;
}

SDL_Rect AbstractEntity::getHitBox() {
    return mHitBox;
}
