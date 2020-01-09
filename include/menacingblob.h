#ifndef _MENACING_BLOB_
#define _MENACING_BLOB_

#include<texturewrapper.h>
#include<SDL2/SDL.h>
#include <abstractenemy.h>

class MenacingBlob: public AbstractEnemy {
    public:
    static const int BLOB_WIDTH = 30;
    static const int BLOB_HEIGHT = 30;
    static const int MAX_SPEED = 2;
    static const int WALKING_FRAMES = 2;

    MenacingBlob(int x, int y);
    ~MenacingBlob();

    void move() override;
    void render() override;

    static bool init(TextureWrapper* texture);

    private:
    static TextureWrapper* TEXTURE;
    static SDL_Rect BLOB_CLIPS[];
};

#endif