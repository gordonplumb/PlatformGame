#ifndef MOVEMENTSTRATEGY_H
#define MOVEMENTSTRATEGY_H

class MovementStrategy {
    public:
    virtual void move(int& xVel, int& yVel, int xPos, int yPos, int speed,
        int playerX, int playerY);
};

#endif