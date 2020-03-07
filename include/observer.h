#ifndef OBSERVER_H
#define OBSERVER_H

class SDL_Point;
class TextureWrapper;
class View;

class Observer {
    protected:
    View* view;
    int id; // id corresponding to object it is observing
    TextureWrapper* texture;
    int xOffset;
    int yOffset;

    void removeFromView();

    public:
    Observer(int id, View* view, TextureWrapper* texture,
        int xOffset, int yOffset);
    virtual ~Observer() = 0;

    virtual void notify(int hp, int xPos, int yPos, bool forward, bool crouching,
        bool lookingUp, bool walking, double angle = 0,
        SDL_Point* centre = nullptr) = 0;
};

#endif