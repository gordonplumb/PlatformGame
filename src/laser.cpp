#include <laser.h>

TextureWrapper* Laser::TEXTURE;


Laser::Laser(int x, int y, int xModifier, int yModifier):
    AbstractEntity(LASER_WIDTH, LASER_HEIGHT, LASER_MAX_SPEED, x, y, 1), xModifier {xModifier}, yModifier {yModifier} {}

Laser::~Laser() {}

bool Laser::init(TextureWrapper* texture) {
    TEXTURE = texture;
    return true;
}

void Laser::move(int top, int bot, int right, int left) {
    // modify this to allow lasers to be shot vertically
    mPosX += LASER_MAX_SPEED * xModifier;
    mPosY += 0;
    mHitBox.x = mPosX;
    mHitBox.y = mPosY;
}

void Laser::render(int camX, int camY) {
    TEXTURE->render(mHitBox.x, mHitBox.y, camX, camY);
}