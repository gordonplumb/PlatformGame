#ifndef _WALL_H_
#define _WALL_H_

#include <SDL2/SDL.h>

class TextureWrapper;

class Wall {
    SDL_Rect rect;

    public:
    Wall(int x, int y, int w, int h);
    ~Wall();

    SDL_Rect getHitBox();
};

#endif