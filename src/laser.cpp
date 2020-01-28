#include <laser.h>

TextureWrapper* Laser::TEXTURE;


Laser::Laser(int x, int y, bool horizontal, bool vertical, int xModifier,
             int yModifier):
    AbstractEntity {LASER_WIDTH, LASER_HEIGHT, LASER_MAX_SPEED, x, y, 1, 1} {
    if (horizontal && vertical) {
        // TODO: change this, also hitbox needs to be modified for diagonal
        mVelX = 7 * xModifier;
        mVelY = 7 * yModifier;
    } else if (horizontal) {
        mVelX = LASER_MAX_SPEED * xModifier;
        mVelY = 0;
    } else {
        mVelX = 0;
        mVelY = LASER_MAX_SPEED * yModifier;
    }
}

Laser::~Laser() {}

bool Laser::init(TextureWrapper* texture) {
    TEXTURE = texture;
    return true;
}

void Laser::move(int top, int bot, int right, int left) {
    mPosX += mVelX;
    mPosY += mVelY;;
    mHitBox.x = mPosX;
    mHitBox.y = mPosY;
}

void Laser::render(int camX, int camY) {
    double angle = 0;
    SDL_Point *centre = new SDL_Point {mWidth / 2, mHeight / 2};
    if (mVelX == 0) {
        angle = 90;
    } else if (mVelY < 0) {
        if (mVelX > 0) {
            angle = -45;
        } else {
            angle = 45;
        }
    }
    TEXTURE->render(mHitBox.x, mHitBox.y, camX, camY, nullptr, angle, centre);
}