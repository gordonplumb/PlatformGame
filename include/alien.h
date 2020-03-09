#ifndef ALIEN_H
#define ALIEN_H

#include <memory>
#include <abstractenemy.h>

class Observer;

class Alien: public AbstractEnemy {
    public:
    static const int WIDTH = 20;
    static const int HEIGHT = 70;
    static const int MAX_SPEED = 1;
    static const int MAX_HP = 3;
    static const int DAMAGE = 2;

    Alien(int x, int y, std::unique_ptr<MovementStrategy>& strategy, 
        std::unique_ptr<Observer> observer);
    ~Alien();
};

#endif