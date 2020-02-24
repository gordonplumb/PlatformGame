#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <abstractentity.h>

class Laser;
class Observer;

class Player: public AbstractEntity {    
    public:
    static const int PLAYER_WIDTH = 40;
    static const int PLAYER_HEIGHT = 70;
    static const int PLAYER_MAX_SPEED = 3;

    Player(Observer* observer);

    ~Player();

    void move(uint32_t time) override;
    void notifyObservers() override;

    Laser* fireLaser();
};


#endif