#ifndef _LASER_
#define _LASER_

#include <abstractentity.h>

class SDL_Point;

class Laser: public AbstractEntity {
    double angle;
    SDL_Point* centre;
    bool mHorizontal;
    bool mVertical;
    int mXModifier;
    int mYModifier;

    public:
    static const int LASER_WIDTH = 20;
    static const int LASER_HEIGHT = 5;
    static const int LASER_MAX_SPEED = 10;

    Laser(int x, int y, bool horizontal, bool vertical, int xModifier,
          int yModifier, int damage);
    ~Laser();

    void move(uint32_t time) override;
    void notifyObservers() override;
};

#endif