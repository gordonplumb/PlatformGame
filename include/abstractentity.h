#ifndef _ABSTRACT_ENTITY_
#define _ABSTRACT_ENTITY_

#include <SDL2/SDL.h>
#include <texturewrapper.h>

class AbstractEntity {
    public:
    AbstractEntity(int width, int height, int maxSpeed, int posX,
                   int posY, int maxWalkingFrame);
    virtual ~AbstractEntity() {}

    virtual void move() = 0;
    virtual void render() = 0;

    void changePosX(int amount);
    void changePosY(int amount);
    void applyGravity();
    bool canJump();
    void setJump(bool canJump);
    void reverse();

    int getVelX();
    int getVelY();
    void changeVelX(int velX);
    void changeVelY(int VelY);
    SDL_Rect getHitBox();

    protected:
    int mWidth;
    int mHeight;
    int mMaxSpeed;
    int mPosX;
    int mPosY;
    int mVelX = 0;
    int mVelY = 0;

    bool mForward = true;
    bool mCanJump = false;

    int mWalkingFrame = 0;
    int mMaxWalkingFrame;

    SDL_Rect mHitBox;
};

#endif