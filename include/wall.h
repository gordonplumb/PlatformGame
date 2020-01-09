#ifndef _WALL_H_
#define _WALL_H_

#include <SDL2/SDL.h>

class TextureWrapper;

class Wall {
    SDL_Rect rect;
    static TextureWrapper* TEXTURE;
    static int DIM;

    public:
    Wall(int x, int y, int w, int h);
    ~Wall();

    static bool init(TextureWrapper* texture, int dim);
    void render();
    SDL_Rect getHitBox();
};

#endif