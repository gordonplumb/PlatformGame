#ifndef LASER_H
#define LASER_H

#include <memory>
#include <abstractentity.h>
#include <observer.h>

class SDL_Point;
class Observer;

class Laser: public AbstractEntity {
    double angle;
    bool horizontal;
    bool vertical;
    int xModifier;
    int yModifier;

    public:
    static const int LASER_WIDTH = 20;
    static const int LASER_HEIGHT = 5;
    static const int LASER_MAX_SPEED = 10;

    Laser(int x, int y, bool horizontal, bool vertical, int xModifier,
        int yModifier, int damage, std::unique_ptr<Observer> observer);
    ~Laser();

    void move();
    void notifyObservers() override;
};

#endif