#include <SDL2/SDL.h>
#include <observer.h>
#include <view.h>
#include <texturewrapper.h>

Observer::Observer(int id, View* view, TextureWrapper* texture,
    int xOffset, int yOffset): id(id), view(view), texture(texture),
    xOffset(xOffset), yOffset(yOffset) {}

Observer::~Observer() {}

void Observer::removeFromView() {
    view->removeObserver(this);
}
