#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <abstractenemy.h>

class Observer;

class Zombie: public AbstractEnemy {
    public:
    static const int WIDTH = 40;
    static const int HEIGHT = 80;
    static const int MAX_SPEED = 1;
    static const int MAX_HP = 3;
    static const int DAMAGE = 2;

    Zombie(int x, int y, MovementStrategy* strategy, Observer* observer);
    ~Zombie();
};

#endif