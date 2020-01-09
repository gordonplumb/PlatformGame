#include <player.h>
#include <laser.h>

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

TextureWrapper* Player::TEXTURE;
SDL_Rect Player::PLAYER_CLIPS[ 3 ];
const int Player::PLAYER_WIDTH = 50;
const int Player::PLAYER_HEIGHT = 100;
const int Player::PLAYER_MAX_SPEED = 3;
const int Player::PLAYER_WALKING_FRAMES = 3;

Player::Player(): AbstractEntity(PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_MAX_SPEED,
                                 100, 200, PLAYER_WALKING_FRAMES) {
}

Player::~Player() {}

bool Player::init(TextureWrapper* texture) {
    TEXTURE = texture;
    PLAYER_CLIPS[0].x = 0;
    PLAYER_CLIPS[0].y = 0;
    PLAYER_CLIPS[0].w = PLAYER_WIDTH;
    PLAYER_CLIPS[0].h = PLAYER_HEIGHT;

    PLAYER_CLIPS[1].x = PLAYER_WIDTH;
    PLAYER_CLIPS[1].y = 0;
    PLAYER_CLIPS[1].w = PLAYER_WIDTH;
    PLAYER_CLIPS[1].h = PLAYER_HEIGHT;

    PLAYER_CLIPS[2].x = PLAYER_WIDTH * 2;
    PLAYER_CLIPS[2].y = 0;
    PLAYER_CLIPS[2].w = PLAYER_WIDTH;
    PLAYER_CLIPS[2].h = PLAYER_HEIGHT;

    return true;
}

void Player::handleEvent(SDL_Event& event) {

}

void Player::move() {
    applyGravity();
    mPosX += mVelX;
    if ((mPosX < 0) || (mPosX + PLAYER_WIDTH > SCREEN_WIDTH)) {
        mPosX -= mVelX;
    }

    // determine direction to face
    if (mVelX != 0) {
        mForward = mVelX > 0;
    }

    mPosY += mVelY;
    if ((mPosY < 0) || (mPosY + PLAYER_HEIGHT > SCREEN_HEIGHT)) {
        mPosY -= mVelY;
    }
    mHitBox.x = mPosX;
    mHitBox.y = mPosY;
}

void Player::render() {
    SDL_Rect clip;
    if (mVelX == 0) {
        clip = PLAYER_CLIPS[0];
        mWalkingFrame = 0;
    } else {
        clip = PLAYER_CLIPS[mWalkingFrame / 6];
        mWalkingFrame++;
        if (mWalkingFrame / 6 >= mMaxWalkingFrame) {
            mWalkingFrame = 0;
        }
    }
    
    TEXTURE->render(mPosX, mPosY, &clip, 0.0, NULL,
                    mForward ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
}

Laser* Player::fireLaser() {
    int x = mHitBox.x;
    int y = mHitBox.y + 55;
    if (mForward) {
        x += 45;
    } else {
        x -= 20;
    }

    return new Laser(x, y, mForward ? 1 : -1, 1);
}
