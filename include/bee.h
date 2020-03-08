#ifndef BEE_H
#define BEE_H

#include <memory>
#include <abstractenemy.h>

class Bee: public AbstractEnemy {
    public:
    static const int WIDTH = 30;
    static const int HEIGHT = 20;
    static const int MAX_SPEED = 1;
    static const int MAX_HP = 1;
    static const int DAMAGE = 1;

    Bee(int x, int y, std::unique_ptr<MovementStrategy>& strategy,
        std::unique_ptr<Observer> observer);
    ~Bee();

    void move(int playerX, int playerY) override;
};

#endif