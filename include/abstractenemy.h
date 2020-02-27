#ifndef _ABSTRACT_ENEMY_
#define _ABSTRACT_ENEMY_

#include <abstractentity.h>

class Observer;
class MovementStrategy;

class AbstractEnemy: public AbstractEntity {
    protected:
    MovementStrategy* strategy;

    public:
    AbstractEnemy(int width, int height, int maxSpeed, int x, int y,
        int totalHP, int damage, MovementStrategy* strategy,
        Observer* observer);
    ~AbstractEnemy();

    virtual void move(int playerx = -1, int playery = -1);
};

#endif