#ifndef _MOVEMENT_STRATEGY_H
#define _MOVEMENT_STRATEGY_H

class MovementStrategy {
    public:
    virtual void move(int& velx, int& vely, int posx, int posy, int speed,
        int playerx, int playery);
};

#endif