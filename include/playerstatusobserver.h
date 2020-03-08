#ifndef PLAYERSTATUSOBSERVER_H
#define PLAYERSTATUSOBSERVER_H

#include <memory>
#include <observer.h>

class View;
class TextureWrapper;
class SDL_Point;

class PlayerStatusObserver: public Observer {
    public:
    PlayerStatusObserver(std::shared_ptr<View> view,
        std::shared_ptr<TextureWrapper> texture);
    ~PlayerStatusObserver();

    void notify(int hp, int xPos, int yPos, bool forward, bool crouching,
        bool lookingUp, bool walking, double angle, SDL_Point centre) override;
};

#endif