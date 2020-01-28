#include <abstractentity.h>
#include <abstractenemy.h>

AbstractEnemy::AbstractEnemy(int width, int height, int maxSpeed, int x, int y,
                             int totalHP, int maxWalkingFrame): 
    AbstractEntity(width, height, maxSpeed, x, y, totalHP, maxWalkingFrame) {}

AbstractEnemy::~AbstractEnemy() {}
