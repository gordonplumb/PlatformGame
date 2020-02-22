#include <SDL2/SDL.h>
#include <observer.h>
#include <view.h>
#include <texturewrapper.h>
#include <gameconstants.h>

Observer::Observer(int id, View* view, TextureWrapper* texture,
                   int xOffset, int yOffset) {
    this->id = id;
    this->view = view;
    this->texture = texture;
    this->xOffset = xOffset;
    this->yOffset = yOffset;
}

Observer::~Observer() {}

void Observer::removeFromView() {
    view->removeObserver(this);
}
