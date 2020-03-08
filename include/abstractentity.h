#ifndef ABSTRACTENTITY_H
#define ABSTRACTENTITY_H

#include <memory>
#include <vector>
#include <SDL2/SDL.h>

class Observer;

class AbstractEntity {
    protected:
    // position and hitbox
    int xPos;
    int yPos;
    int width;
    int height;

    // movement
    int maxSpeed;
    int xVel = 0;
    int yVel = 0;
    int xRecoil = 0;
    int yRecoil = 0;

    // movement states
    bool forward = true;
    bool crouching = false;
    bool lookingUp = false;
    bool canJump = false;

    // combat
    int totalHP;
    int hitpoints;
    int damage;
    bool invincible = false;
    uint32_t invincibilityTimer = 0;

    std::vector<std::unique_ptr<Observer>> observers;

    public:
    AbstractEntity(int width, int height, int maxSpeed, int xPos,
        int yPos, int totalHP, int damage);
    virtual ~AbstractEntity();

    virtual void notifyObservers();
    void addObserver(std::unique_ptr<Observer> observer);

    void applyGravity();
    void removeRecoil();

    void changeHP(int amount);
    void changePosX(int amount);
    void changePosY(int amount);
    void changeVelX(int velX);
    void changeVelY(int velY);
    void setXRecoil(int recoil);
    void setYRecoil(int recoil);
    void setJump(bool canJump);
    void setCrouch(bool crouching);
    void setLookingUp(bool lookingUp);
    void setInvincibility(bool invincible, uint32_t time);

    SDL_Rect getHitBox();
    int getTotalHP();
    int getHP();
    int getDamage();
    int getVelX();
    int getVelY();
    bool getJump();
    bool isForward();
    bool isCrouching();
    bool isLookingUp();
    bool isInvincible();
};

#endif