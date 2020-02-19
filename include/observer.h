#ifndef _OBSERVER_
#define _OBSERVER_

class SDL_Point;
class TextureWrapper;
class View;

class Observer {
    View* view;
    int id; // id corresponding to object it is observing
    TextureWrapper* texture;
    int xOffset;
    int yOffset;
    int walkingFrame = 0;
    int maxWalkingFrame;

    void removeFromView();

    public:
    Observer(int id, View* view, TextureWrapper* texture, int maxWalkFrame,
             int xOffset, int yOffset);
    ~Observer();

    virtual void notify(int xPos, int yPos, bool forward, bool crouching,
                        bool lookingUp, bool walking, double angle = 0,
                        SDL_Point* centre = nullptr);
    
    int getId();
};

#endif