#ifndef _MENACING_BLOB_
#define _MENACING_BLOB_

#include <abstractenemy.h>

class Observer;

class MenacingBlob: public AbstractEnemy {
    public:
    static const int WIDTH = 30;
    static const int HEIGHT = 30;
    static const int MAX_SPEED = 2;
    static const int MAX_HP = 1;
    static const int DAMAGE = 1;

    MenacingBlob(int x, int y, MovementStrategy* strategy, Observer* observer);
    ~MenacingBlob();
};

#endif