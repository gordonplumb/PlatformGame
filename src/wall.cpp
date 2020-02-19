#include <SDL2/SDL.h>
#include <texturewrapper.h>
#include <wall.h>

Wall::Wall(int x, int y, int w, int h) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

SDL_Rect Wall::getHitBox() {
    return rect;
}
