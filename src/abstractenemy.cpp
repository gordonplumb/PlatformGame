#include <abstractenemy.h>
#include <observer.h>

AbstractEnemy::AbstractEnemy(int width, int height, int maxSpeed, int x, int y,
                             int totalHP, int damage, Observer* observer): 
    AbstractEntity(width, height, maxSpeed, x, y, totalHP, damage) {
    addObserver(observer);
}

AbstractEnemy::~AbstractEnemy() {}
