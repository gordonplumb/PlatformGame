#include <memory>
#include <SDL2/SDL.h>
#include <gameconstants.h>
#include <view.h>
#include <movingobserver.h>
#include <texturewrapper.h>

using namespace std;

MovingObserver::MovingObserver(int id, shared_ptr<View> view,
    shared_ptr<TextureWrapper> texture, int maxWalkFrame, int xOffset,
    int yOffset):
    Observer(id, view, texture, xOffset, yOffset), maxWalkingFrame(maxWalkFrame)
    {}

MovingObserver::~MovingObserver() {}

void MovingObserver::notify(int hp, int xPos, int yPos, bool forward,
    bool crouching, bool lookingUp, bool walking, double angle, 
    SDL_Point centre) {
    int clip;

    if (crouching) {
        clip = 7;
        walkingFrame = 0;
    } else if (!walking) {
        clip = lookingUp ? 6 : 0;
        walkingFrame = 0;
    } else {
        int index = walkingFrame / 6;
        if (lookingUp) index += 3;
        clip = index;
        walkingFrame++;
        if (walkingFrame / 6 > maxWalkingFrame) {
            walkingFrame = 0;
        }
    }
    
    if (id == PLAYER_ID) {
        view->updateCamera(centre);
    }
    SDL_Rect camera = view->getCamera();

    texture->render(view->getRenderer(), xPos - xOffset, yPos - yOffset,
        camera.x, camera.y, clip, angle, &centre,
        forward ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
}