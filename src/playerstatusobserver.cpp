#include <playerstatusobserver.h>
#include <observer.h>
#include <gameconstants.h>
#include <view.h>
#include <texturewrapper.h>

PlayerStatusObserver::PlayerStatusObserver(View* view,
    TextureWrapper* texture): Observer(PLAYER_ID, view, texture, 0, 0) {}

PlayerStatusObserver::~PlayerStatusObserver() {
    removeFromView();
}

void PlayerStatusObserver::notify(int hp, int xPos, int yPos, bool forward,
                                  bool crouching, bool lookingUp, bool walking,
                                  double angle, SDL_Point* centre) {
    SDL_Rect* camera = view->getCamera();
    for (int i = 0; i < hp; i++) {
        texture->render(view->getRenderer(), 5 + 30 * i, 5, camera->x, camera->y);
    }
}