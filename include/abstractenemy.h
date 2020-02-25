#ifndef _ABSTRACT_ENEMY_
#define _ABSTRACT_ENEMY_

#include <abstractentity.h>

class Observer;

class AbstractEnemy: public AbstractEntity {
    public:
    AbstractEnemy(int width, int height, int maxSpeed, int x, int y,
                  int totalHP, int damage, Observer* observer);
    ~AbstractEnemy();
};

#endif