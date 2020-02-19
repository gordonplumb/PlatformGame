#include <SDL2/SDL.h>
#include <observer.h>
#include <view.h>
#include <texturewrapper.h>
#include <gameconstants.h>

Observer::Observer(int id, View* view, TextureWrapper* texture,
                   int maxWalkFrame, int xOffset, int yOffset) {
    this->id = id;
    this->view = view;
    this->texture = texture;
    this->maxWalkingFrame = maxWalkFrame;
    this->xOffset = xOffset;
    this->yOffset = yOffset;
}

Observer::~Observer() {
    removeFromView();
}

int Observer::getId() {
    return id;
}

void Observer::notify(int xPos, int yPos, bool forward, bool crouching,
                      bool lookingUp, bool walking, double angle,
                      SDL_Point* centre) {
    SDL_Rect* clip;

    if (crouching) {
        clip = texture->getClip(7);
        walkingFrame = 0;
    } else if (!walking) {
        clip = lookingUp ? texture->getClip(6) : texture->getClip(0);
        walkingFrame = 0;
    } else {
        int index = walkingFrame / 6;
        if (lookingUp) index += 3;
        clip = texture->getClip(index);
        walkingFrame++;
        if (walkingFrame / 6 > maxWalkingFrame) {
            walkingFrame = 0;
        }
    }
    
    if (id == PLAYER_ID) {
        view->updateCamera(centre);
    }
    SDL_Rect* camera = view->getCamera();

    texture->render(view->getRenderer(), xPos - xOffset, yPos - yOffset,
                    camera->x, camera->y, clip, angle, centre,
                    forward ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
}

void Observer::removeFromView() {
    view->removeObserver(this);
}
