#include <memory>
#include <playerstatusobserver.h>
#include <observer.h>
#include <gameconstants.h>
#include <view.h>
#include <texturewrapper.h>

using namespace std;

PlayerStatusObserver::PlayerStatusObserver(shared_ptr<View> view,
    shared_ptr<TextureWrapper> texture): Observer(PLAYER_ID, view, texture, 0,
    0) {}

PlayerStatusObserver::~PlayerStatusObserver() {}

void PlayerStatusObserver::notify(int hp, int xPos, int yPos, bool forward,
    bool crouching, bool lookingUp, bool walking, double angle,
    SDL_Point centre) {
    for (int i = 0; i < hp; i++) {
        texture->render(view->getRenderer(), 5 + 30 * i, 5, 0, 0);
    }
}