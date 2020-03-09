#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <abstractentity.h>

class Laser;
class Observer;

class Player: public AbstractEntity {    
    public:
    static const int PLAYER_WIDTH = 44;
    static const int PLAYER_HEIGHT = 72;
    static const int PLAYER_MAX_SPEED = 3;

    Player(std::unique_ptr<Observer> observer);

    ~Player();

    void move(uint32_t time);
    void notifyObservers() override;
    void setPos(int x = 0, int y = 0);
    void reset();
};


#endif