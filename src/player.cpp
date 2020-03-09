#include <memory>
#include <gameconstants.h>
#include <player.h>
#include <laser.h>
#include <observer.h>

using namespace std;

Player::Player(unique_ptr<Observer> observer):
    AbstractEntity(PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_MAX_SPEED, 0, 0, 10, 0) {
    addObserver(std::move(observer));
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
    SDL_Point centre = {xPos + width / 2, yPos + height / 2};
    for (auto& observer : observers) {
        observer->notify(hitpoints, xPos, yPos, forward, crouching, lookingUp,
                         xVel != 0, 0, centre);
    }
}

void Player::setPos(int x, int y) {
    xPos = x;
    yPos = y;
}

void Player::reset() {
    setPos();
    xVel = 0;
    yVel = 0;
    lookingUp = false;
    crouching = false;
}
