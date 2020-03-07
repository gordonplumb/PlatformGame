#ifndef WALL_H
#define WALL_H

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