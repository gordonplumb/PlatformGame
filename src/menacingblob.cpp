#include <abstractenemy.h>
#include <menacingblob.h>
#include <observer.h>

MenacingBlob::MenacingBlob(int x, int y, MovementStrategy* strategy,
    Observer* observer): 
    AbstractEnemy(WIDTH, HEIGHT, MAX_SPEED, x, y, MAX_HP, DAMAGE, strategy,
        observer) {}

MenacingBlob::~MenacingBlob() {}
