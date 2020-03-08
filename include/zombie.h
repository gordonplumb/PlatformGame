#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <memory>
#include <abstractenemy.h>

class Observer;

class Zombie: public AbstractEnemy {
    public:
    static const int WIDTH = 40;
    static const int HEIGHT = 80;
    static const int MAX_SPEED = 1;
    static const int MAX_HP = 3;
    static const int DAMAGE = 2;

    Zombie(int x, int y, std::unique_ptr<MovementStrategy>& strategy, 
        std::unique_ptr<Observer> observer);
    ~Zombie();
};

#endif