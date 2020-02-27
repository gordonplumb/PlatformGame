#include <abstractenemy.h>
#include <zombie.h>
#include <observer.h>

Zombie::Zombie(int x, int y, MovementStrategy* strategy, Observer* observer): 
    AbstractEnemy(WIDTH, HEIGHT, MAX_SPEED, x, y, MAX_HP, DAMAGE, strategy,
        observer) {}

Zombie::~Zombie() {}
