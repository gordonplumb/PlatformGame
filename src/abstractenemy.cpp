#include <abstractenemy.h>
#include <observer.h>

AbstractEnemy::AbstractEnemy(int width, int height, int maxSpeed, int x, int y,
                             int totalHP, Observer* observer): 
    AbstractEntity(width, height, maxSpeed, x, y, totalHP) {
    addObserver(observer);
}

AbstractEnemy::~AbstractEnemy() {}
