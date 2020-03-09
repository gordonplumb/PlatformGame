#include <memory>
#include <abstractenemy.h>
#include <alien.h>
#include <observer.h>
#include <movementstrategy.h>

using namespace std;

Alien::Alien(int x, int y, unique_ptr<MovementStrategy>& strategy,
    unique_ptr<Observer> observer): 
    AbstractEnemy(WIDTH, HEIGHT, MAX_SPEED, x, y, MAX_HP, DAMAGE,
        std::move(strategy), std::move(observer)) {}

Alien::~Alien() {}
