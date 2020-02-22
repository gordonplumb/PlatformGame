#ifndef _PLAYER_STATUS_OBSERVER_
#define _PLAYER_STATUS_OBSERVER_

#include <observer.h>

class View;
class TextureWrapper;
class SDL_Point;

class PlayerStatusObserver: public Observer {
    public:
    PlayerStatusObserver(View* view, TextureWrapper* texture);
    ~PlayerStatusObserver();

    void notify(int hp, int xPos, int yPos, bool forward, bool crouching,
                bool lookingUp, bool walking, double angle = 0,
                SDL_Point* centre = nullptr) override;
};

#endif