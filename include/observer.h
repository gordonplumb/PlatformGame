#ifndef OBSERVER_H
#define OBSERVER_H

#include <memory>
#include <SDL2/SDL.h>

class TextureWrapper;
class View;

class Observer {
    protected:
    std::shared_ptr<View> view;
    int id; // id corresponding to object it is observing
    std::shared_ptr<TextureWrapper> texture;
    int xOffset;
    int yOffset;

    public:
    Observer(int id, std::shared_ptr<View> view,
        std::shared_ptr<TextureWrapper> texture, int xOffset, int yOffset);
    virtual ~Observer() = 0;

    virtual void notify(int hp, int xPos, int yPos, bool forward,
        bool crouching, bool lookingUp, bool walking, double angle = 0,
        SDL_Point centre = {-1, -1}) = 0;
};

#endif