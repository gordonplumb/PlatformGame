#ifndef _ABSTRACT_ENTITY_
#define _ABSTRACT_ENTITY_

#include <vector>
#include <SDL2/SDL.h>

class Observer;

class AbstractEntity {
    protected:
    int id;
    int mWidth;
    int mHeight;
    int mMaxSpeed;
    int mPosX;
    int mPosY;
    int mVelX = 0;
    int mVelY = 0;
    int xRecoil = 0;
    int yRecoil = 0;
    int mTotalHP;
    int mHP;
    int damage;

    bool invincible = false;
    uint32_t invincibilityTimer = 0;

    bool mForward = true;
    bool mCrouching = false;
    bool mLookingUp = false;
    bool mCanJump = false;

    SDL_Rect mHitBox;
    std::vector<Observer*> observers;

    public:
    AbstractEntity(int width, int height, int maxSpeed, int posX,
                   int posY, int totalHP, int damage);
    virtual ~AbstractEntity();

    virtual void move(uint32_t time);
    virtual void notifyObservers();

    void addObserver(Observer* observer);
    void changePosX(int amount);
    void changePosY(int amount);
    void changeVelX(int velX);
    void changeVelY(int velY);
    void setXRecoil(int recoil);
    void setYRecoil(int recoil);
    void changeHP(int amount);
    void setJump(bool canJump);
    void setCrouch(bool crouching);
    void setLookingUp(bool lookingUp);
    void setInvincibility(bool invincible, uint32_t time);
    void applyGravity();
    void removeRecoil();
    void reverse();

    bool canJump();
    bool isCrouching();
    bool isLookingUp();
    bool isInvincible();
    int getVelX();
    int getVelY();
    int getTotalHP();
    int getHP();
    int getDamage();
    SDL_Rect getHitBox();
};

#endif