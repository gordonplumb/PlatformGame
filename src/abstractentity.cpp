#include <abstractentity.h>
#include <observer.h>

AbstractEntity::AbstractEntity(int width, int height, int maxSpeed, int posX,
                               int posY, int totalHP, int damage) {
    mWidth = width;
    mHeight = height;
    mMaxSpeed = maxSpeed;
    mPosX = posX;
    mPosY = posY;
    mTotalHP = totalHP;
    mHP = totalHP;
    mHitBox.x = mPosX;
    mHitBox.y = mPosY;
    mHitBox.w = width;
    mHitBox.h = height;
    this->damage = damage;
}

AbstractEntity::~AbstractEntity() {
    for (Observer* observer : observers) {
        delete observer;
    }
}

void AbstractEntity::changePosX(int amount) {
    mPosX += amount;
    mHitBox.x += amount;
}

void AbstractEntity::changePosY(int amount) {
    mPosY += amount;
    mHitBox.y += amount;
}

void AbstractEntity::applyGravity() {
    mVelY += 1;
}

void AbstractEntity::removeRecoil() {
    if (xRecoil != 0) {
        int xRemoveRecoil = xRecoil - xRecoil / 2;
        mVelX -= xRemoveRecoil;
        xRecoil -= xRemoveRecoil;
    }
    if (yRecoil != 0) {
        int yRemoveRecoil = yRecoil - yRecoil / 2;
        mVelY -= yRemoveRecoil;
        yRecoil -= yRemoveRecoil;
    }
}

bool AbstractEntity::canJump() {
    // y vel > 1 means entity is falling or being pushed down
    return mCanJump && mVelY <= 1;
}

bool AbstractEntity::isCrouching() {
    return mCrouching;
}

bool AbstractEntity::isLookingUp() {
    return mLookingUp;
}

bool AbstractEntity::isInvincible() {
    return invincible;
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

void AbstractEntity::setInvincibility(bool invincible, uint32_t time) {
    this->invincible = invincible;
    if (invincible) {
        invincibilityTimer = time;
    }
}

void AbstractEntity::reverse() {
    mPosX -= mVelX;
    mPosY -= mVelY;
}

void AbstractEntity::addObserver(Observer* observer) {
    this->observers.push_back(observer);
}

void AbstractEntity::notifyObservers() {
    for (Observer* observer : observers) {
        observer->notify(mHP, mPosX, mPosY, mForward, mCrouching, mLookingUp,
                         mVelX != 0);
    }
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

int AbstractEntity::getDamage() {
    return damage;
}

void AbstractEntity::changeVelX(int velX) {
    mVelX += velX;
}

void AbstractEntity::changeVelY(int velY) {
    mVelY += velY;
}

void AbstractEntity::setXRecoil(int recoil) {
    xRecoil = recoil;
    mVelX += recoil;
}

void AbstractEntity::setYRecoil(int recoil) {
    yRecoil = recoil;
    mVelY += recoil;
}

void AbstractEntity::changeHP(int amount) {
    mHP += amount;
}

SDL_Rect AbstractEntity::getHitBox() {
    return mHitBox;
}
