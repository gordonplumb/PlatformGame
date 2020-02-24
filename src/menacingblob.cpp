#include <menacingblob.h>
#include <observer.h>

MenacingBlob::MenacingBlob(int x, int y, Observer* observer): 
    AbstractEnemy(BLOB_WIDTH, BLOB_HEIGHT, MAX_SPEED, x, y, 1, observer) {}

MenacingBlob::~MenacingBlob() {}

void MenacingBlob::move(uint32_t time) {
    // TODO: different movement behaviour
    AbstractEntity::move(time);
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
    
    mHitBox.x = mPosX;
    mHitBox.y = mPosY;
    removeRecoil();
}
