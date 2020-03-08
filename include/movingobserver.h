#ifndef MOVINGOBSERVER_H
#define MOVINGOBSERVER_H

#include <memory>
#include <observer.h>

class View;
class TextureWrapper;
class SDL_Point;

class MovingObserver: public Observer {
    int walkingFrame = 0;
    int maxWalkingFrame;

    public:
    MovingObserver(int id, std::shared_ptr<View> view,
        std::shared_ptr<TextureWrapper> texture, int maxWalkFrame, int xOffset,
        int yOffset);
    ~MovingObserver();

    void notify(int hp, int xPos, int yPos, bool forward, bool crouching,
        bool lookingUp, bool walking, double angle, SDL_Point centre) override;
};

#endif