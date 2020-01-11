#include <SDL2/SDL.h>
#include <texturewrapper.h>
#include <wall.h>

TextureWrapper* Wall::TEXTURE;
int Wall::DIM;

Wall::Wall(int x, int y, int w, int h) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

bool Wall::init(TextureWrapper* texture, int dim) {
    TEXTURE = texture;
    DIM = dim;

    return true;
}

void Wall::render(int camX, int camY) {
    for (int i = 0; i < rect.h / DIM; i++) {
        for (int j = 0; j < rect.w / DIM; j++) {
            TEXTURE->render(rect.x + j * DIM, rect.y + i * DIM, camX, camY);
        }
    }
}

SDL_Rect Wall::getHitBox() {
    return rect;
}
