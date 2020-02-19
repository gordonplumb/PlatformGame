#include <menacingblob.h>
#include <observer.h>

MenacingBlob::MenacingBlob(int x, int y, Observer* observer): 
    AbstractEnemy(BLOB_WIDTH, BLOB_HEIGHT, MAX_SPEED, x, y, 1, observer) {}

MenacingBlob::~MenacingBlob() {}

void MenacingBlob::move(int top, int bot, int left, int right) {
    // TODO: different movement behaviour
    applyGravity();
    if (mPosX <= 200) {
        mVelX = MAX_SPEED;
    } else if (mPosX >= 300) {
        mVelX = MAX_SPEED * -1;
    }

    mPosX += mVelX;
    mPosY += mVelY;

    if (mVelX != 0) {
        mForward = !(mVelX > 0);
    }
    if (mPosX < left || mPosX + BLOB_WIDTH > right) {
        mPosX -= mVelX;
    }

    if (mPosY < top || mPosY + BLOB_HEIGHT > bot) {
        mPosY -= mVelY;
    }
    mHitBox.x = mPosX;
    mHitBox.y = mPosY;
}
