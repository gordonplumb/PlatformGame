#ifndef PLAYERSTATUSOBSERVER_H
#define PLAYERSTATUSOBSERVER_H

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