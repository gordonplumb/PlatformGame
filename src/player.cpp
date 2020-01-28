#include <gameconstants.h>
#include <player.h>
#include <laser.h>

TextureWrapper* Player::TEXTURE;
SDL_Rect Player::PLAYER_CLIPS[8];
const int Player::PLAYER_WIDTH = 40;
const int Player::PLAYER_HEIGHT = 70;
const int Player::PLAYER_MAX_SPEED = 3;
const int Player::PLAYER_WALKING_FRAMES = 2;
int Player::TEXTURE_WIDTH;
int Player::TEXTURE_HEIGHT;

Player::Player(): AbstractEntity(PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_MAX_SPEED,
                                 100, 200, 5, PLAYER_WALKING_FRAMES) {
}

Player::~Player() {}

bool Player::init(TextureWrapper* texture, int textureHeight,
                  int textureWidth) {
    TEXTURE = texture;
    TEXTURE_HEIGHT = textureHeight;
    TEXTURE_WIDTH = textureWidth;
    int clipsAdded = 0;

    // walking, aim horizontal clips
    for (int i = 0; i < 3; i++, clipsAdded++) {
        PLAYER_CLIPS[clipsAdded].x = TEXTURE_WIDTH * i;
        PLAYER_CLIPS[clipsAdded].y = 0;
        PLAYER_CLIPS[clipsAdded].w = TEXTURE_WIDTH;
        PLAYER_CLIPS[clipsAdded].h = TEXTURE_HEIGHT;
    }

    // walking, diagonal aim
    for (int i = 0; i < 3; i++, clipsAdded++) {
        PLAYER_CLIPS[clipsAdded].x = TEXTURE_WIDTH * i;
        PLAYER_CLIPS[clipsAdded].y = TEXTURE_HEIGHT;
        PLAYER_CLIPS[clipsAdded].w = TEXTURE_WIDTH;
        PLAYER_CLIPS[clipsAdded].h = TEXTURE_HEIGHT;
    }

    // aiming up
    PLAYER_CLIPS[clipsAdded].x = 0;
    PLAYER_CLIPS[clipsAdded].y = TEXTURE_HEIGHT * 2;
    PLAYER_CLIPS[clipsAdded].w = TEXTURE_WIDTH;
    PLAYER_CLIPS[clipsAdded].h = TEXTURE_HEIGHT;
    clipsAdded++;

    // crouching
    PLAYER_CLIPS[clipsAdded].x = TEXTURE_WIDTH;
    PLAYER_CLIPS[clipsAdded].y = TEXTURE_HEIGHT * 2;
    PLAYER_CLIPS[clipsAdded].w = TEXTURE_WIDTH;
    PLAYER_CLIPS[clipsAdded].h = TEXTURE_HEIGHT;

    return true;
}

void Player::handleEvent(SDL_Event& event) {

}

void Player::move(int top, int bot, int left, int right) {
    applyGravity();
    mPosX += mVelX;
    if ((mPosX < left) || (mPosX + PLAYER_WIDTH > right)) {
        mPosX -= mVelX;
    }

    // determine direction to face
    if (mVelX != 0) {
        mForward = mVelX > 0;
    }

    mPosY += mVelY;
    if ((mPosY < top) || (mPosY + PLAYER_HEIGHT > bot)) {
        mPosY -= mVelY;
    }
    mHitBox.x = mPosX;
    mHitBox.y = mPosY;
}

void Player::render(int camX, int camY) {
    SDL_Rect clip;
    if (mCrouching) {
        clip = PLAYER_CLIPS[7];
        mWalkingFrame = 0;
    } else if (mVelX == 0) {
        clip = mLookingUp ? PLAYER_CLIPS[6]:PLAYER_CLIPS[0];
        mWalkingFrame = 0;
    } else {
        int index = mWalkingFrame / 6;
        if (mLookingUp) index += 3;
        clip = PLAYER_CLIPS[index];
        mWalkingFrame++;
        if (mWalkingFrame / 6 > mMaxWalkingFrame) {
            mWalkingFrame = 0;
        }
    }
    
    int xOffset = (Player::TEXTURE_WIDTH - PLAYER_WIDTH) / 2;
    int yOffset = (Player::TEXTURE_HEIGHT - PLAYER_HEIGHT) / 2;
    TEXTURE->render(mPosX - xOffset, mPosY - yOffset, camX, camY, &clip, 0.0,
                    nullptr, mForward ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
}

Laser* Player::fireLaser() {
    bool horizontal, vertical;
    int x, y;
    int xModifier = mForward ? 1 : -1;
    int yModifier = mLookingUp ? -1 : 1;
    if (mCrouching) {
        horizontal = true;
        x = mHitBox.x + (mForward ? 31 : -10);
        y = mHitBox.y + 52;
    } else if (mLookingUp && mVelX == 0) {
        vertical = true;
        x = mHitBox.x + (mForward ? 35 : 10);
        y = mHitBox.y + 15;
    } else {
        horizontal = true;
        vertical = mLookingUp;
        x = mHitBox.x + (mForward ? 37 : -17);
        y = mHitBox.y + 38;
    }

    return new Laser(x, y, horizontal, vertical, xModifier, yModifier);
}
