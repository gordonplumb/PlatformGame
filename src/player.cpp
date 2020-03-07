#include <gameconstants.h>
#include <player.h>
#include <laser.h>
#include <observer.h>

Player::Player(Observer* observer):
    AbstractEntity(PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_MAX_SPEED, 0, 0, 10, 0) {
    addObserver(observer);
}

Player::~Player() {}

void Player::move(uint32_t time) {
    applyGravity();
    
    // remove invincibility once timer is up
    if (invincible && time > invincibilityTimer + 3 * 1000) {
        invincible = false;
    }

    xPos += xVel;
    yPos += yVel;

    // determine direction to face
    if (xVel - xRecoil != 0) {
        forward = xVel - xRecoil > 0;
    }
}

void Player::notifyObservers() {
    SDL_Point* centre = new SDL_Point {xPos + width / 2, yPos + height / 2};
    for (Observer* observer : observers) {
        observer->notify(hitpoints, xPos, yPos, forward, crouching, lookingUp,
                         xVel != 0, 0, centre);
    }
}

void Player::reset() {
    xPos = 0;
    yPos = 0;
    xVel = 0;
    yVel = 0;
    lookingUp = false;
    crouching = false;
}

Laser* Player::fireLaser() {
    bool horizontal, vertical;
    int x, y;
    int xModifier = forward ? 1 : -1;
    int yModifier = lookingUp ? -1 : 1;
    if (crouching) {
        horizontal = true;
        x = xPos + (forward ? 31 : -10);
        y = yPos + 52;
    } else if (lookingUp && xVel == 0) {
        vertical = true;
        x = xPos + (forward ? 35 : 10);
        y = yPos + 15;
    } else {
        horizontal = true;
        vertical = lookingUp;
        x = xPos + (forward ? 37 : -17);
        y = yPos + 38;
    }

    return new Laser(x, y, horizontal, vertical, xModifier, yModifier, 1);
}
