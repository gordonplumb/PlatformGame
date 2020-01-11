#include <abstractenemy.h>
#include <menacingblob.h>

TextureWrapper* MenacingBlob::TEXTURE;
SDL_Rect MenacingBlob::BLOB_CLIPS[2];

MenacingBlob::MenacingBlob(int x, int y): 
    AbstractEnemy(BLOB_WIDTH, BLOB_HEIGHT, MAX_SPEED, x, y, WALKING_FRAMES) {}

MenacingBlob::~MenacingBlob() {}

void MenacingBlob::move(int top, int bot, int right, int left) {
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

void MenacingBlob::render(int camX, int camY) {
    SDL_Rect clip;

    if (mVelX == 0) {
        clip = BLOB_CLIPS[0];
        mWalkingFrame = 0;
    } else {
        clip = BLOB_CLIPS[mWalkingFrame / 4];
        mWalkingFrame++;

        if (mWalkingFrame / 4 >= mMaxWalkingFrame) {
            mWalkingFrame = 0;
        }
    }

    TEXTURE->render(mPosX, mPosY, camX, camY, &clip, 0.0, NULL,
                    mForward ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
}

bool MenacingBlob::init(TextureWrapper* texture) {
    TEXTURE = texture;
    BLOB_CLIPS[0].x = 0;
    BLOB_CLIPS[0].y = 0;
    BLOB_CLIPS[0].w = BLOB_WIDTH;
    BLOB_CLIPS[0].h = BLOB_HEIGHT;

    BLOB_CLIPS[1].x = BLOB_WIDTH;
    BLOB_CLIPS[1].y = 0;
    BLOB_CLIPS[1].w = BLOB_WIDTH;
    BLOB_CLIPS[1].h = BLOB_HEIGHT;
    return true;
}