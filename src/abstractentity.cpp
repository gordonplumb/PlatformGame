#include <abstractentity.h>
#include <observer.h>

AbstractEntity::AbstractEntity(int width, int height, int maxSpeed, int xPos,
    int yPos, int totalHP, int damage): width(width), height(height),
    maxSpeed(maxSpeed), xPos(xPos), yPos(yPos), totalHP(totalHP),
    hitpoints(totalHP), damage(damage) {}

AbstractEntity::~AbstractEntity() {
    for (Observer* observer : observers) {
        delete observer;
    }
}

void AbstractEntity::changePosX(int amount) {
    xPos += amount;
}

void AbstractEntity::changePosY(int amount) {
    yPos += amount;
}

void AbstractEntity::applyGravity() {
    yVel += 1;
}

void AbstractEntity::removeRecoil() {
    if (xRecoil != 0) {
        int xRemoveRecoil = xRecoil - xRecoil / 2;
        xVel -= xRemoveRecoil;
        xRecoil -= xRemoveRecoil;
    }
    if (yRecoil != 0) {
        int yRemoveRecoil = yRecoil - yRecoil / 2;
        yVel -= yRemoveRecoil;
        yRecoil -= yRemoveRecoil;
    }
}

bool AbstractEntity::getJump() {
    // y vel > 1 means entity is falling or being pushed down
    return canJump && yVel <= 1;
}

bool AbstractEntity::isCrouching() {
    return crouching;
}

bool AbstractEntity::isLookingUp() {
    return lookingUp;
}

bool AbstractEntity::isInvincible() {
    return invincible;
}

void AbstractEntity::setJump(bool canJump) {
    this->canJump = canJump;
    if (canJump) {
        yVel = 0;
    }
}

void AbstractEntity::setCrouch(bool crouching) {
    this->crouching = crouching;
}

void AbstractEntity::setLookingUp(bool lookingUp) {
    this->lookingUp = lookingUp;
}

void AbstractEntity::setInvincibility(bool invincible, uint32_t time) {
    this->invincible = invincible;
    if (invincible) {
        invincibilityTimer = time;
    }
}

void AbstractEntity::addObserver(Observer* observer) {
    this->observers.push_back(observer);
}

void AbstractEntity::notifyObservers() {
    for (Observer* observer : observers) {
        observer->notify(hitpoints, xPos, yPos, forward, crouching, lookingUp,
            xVel != 0);
    }
}

int AbstractEntity::getVelX() {
    return xVel;
}

int AbstractEntity::getVelY() {
    return yVel;
}

int AbstractEntity::getTotalHP() {
    return totalHP;
}

int AbstractEntity::getHP() {
    return hitpoints;
}

int AbstractEntity::getDamage() {
    return damage;
}

void AbstractEntity::changeVelX(int velX) {
    xVel += velX;
}

void AbstractEntity::changeVelY(int velY) {
    yVel += velY;
}

void AbstractEntity::setXRecoil(int recoil) {
    xRecoil = recoil;
    xVel += recoil;
}

void AbstractEntity::setYRecoil(int recoil) {
    yRecoil = recoil;
    yVel += recoil;
}

void AbstractEntity::changeHP(int amount) {
    hitpoints += amount;
}

SDL_Rect AbstractEntity::getHitBox() {
    return {xPos, yPos, width, height};
}
