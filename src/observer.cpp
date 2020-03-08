#include <memory>
#include <SDL2/SDL.h>
#include <observer.h>
#include <view.h>
#include <texturewrapper.h>

using namespace std;

Observer::Observer(int id, shared_ptr<View> view,
    shared_ptr<TextureWrapper> texture, int xOffset, int yOffset): id(id),
    view(view), texture(texture), xOffset(xOffset), yOffset(yOffset) {}

Observer::~Observer() {}
