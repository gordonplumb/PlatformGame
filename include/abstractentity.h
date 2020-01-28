#ifndef _ABSTRACT_ENTITY_
#define _ABSTRACT_ENTITY_

#include <SDL2/SDL.h>
#include <texturewrapper.h>

class AbstractEntity {
    protected:
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

    int mWalkingFrame = 0;
    int mMaxWalkingFrame;

    SDL_Rect mHitBox;

    public:
    AbstractEntity(int width, int height, int maxSpeed, int posX,
                   int posY, int totalHP, int maxWalkingFrame);
    virtual ~AbstractEntity() {}

    virtual void move(int top, int bot, int left, int right) = 0;
    virtual void render(int camX, int camY) = 0;

    void changePosX(int amount);
    void changePosY(int amount);
    void changeVelX(int velX);
    void changeVelY(int velY);
    void changeHP(int amount);
    void applyGravity();
    bool canJump();
    bool isCrouching();
    void setJump(bool canJump);
    void setCrouch(bool crouching);
    void setLookingUp(bool lookingUp);
    void reverse();

    int getVelX();
    int getVelY();
    int getTotalHP();
    int getHP();
    SDL_Rect getHitBox();
};

#endif