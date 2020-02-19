#ifndef _ABSTRACT_ENTITY_
#define _ABSTRACT_ENTITY_

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
    int mTotalHP;
    int mHP;

    bool mForward = true;
    bool mCrouching = false;
    bool mLookingUp = false;
    bool mCanJump = false;

    SDL_Rect mHitBox;
    Observer* observer;

    public:
    AbstractEntity(int width, int height, int maxSpeed, int posX,
                   int posY, int totalHP);
    virtual ~AbstractEntity();

    virtual void move(int top, int bot, int left, int right) = 0;
    virtual void notifyObservers();

    void addObserver(Observer* observer);
    void changePosX(int amount);
    void changePosY(int amount);
    void changeVelX(int velX);
    void changeVelY(int velY);
    void changeHP(int amount);
    void setJump(bool canJump);
    void setCrouch(bool crouching);
    void setLookingUp(bool lookingUp);
    void applyGravity();
    void reverse();

    bool canJump();
    bool isCrouching();
    bool isLookingUp();
    int getVelX();
    int getVelY();
    int getTotalHP();
    int getHP();
    SDL_Rect getHitBox();
};

#endif