#include <SDL2/SDL.h>
#include <abstractentity.h>

AbstractEntity::AbstractEntity(int width, int height, int maxSpeed, int posX,
                               int posY, int maxWalkingFrame) {
    mWidth = width;
    mHeight = height;
    mMaxSpeed = maxSpeed;
    mPosX = posX;
    mPosY = posY;
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

void AbstractEntity::setJump(bool canJump) {
    mCanJump = canJump;
    if (canJump) {
        mVelY = 0;
    }
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

void AbstractEntity::changeVelX(int velX) {
    mVelX += velX;
}

void AbstractEntity::changeVelY(int velY) {
    mVelY += velY;
}

SDL_Rect AbstractEntity::getHitBox() {
    return mHitBox;
}
