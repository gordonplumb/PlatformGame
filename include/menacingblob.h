#ifndef _MENACING_BLOB_
#define _MENACING_BLOB_

#include <abstractenemy.h>

class Observer;

class MenacingBlob: public AbstractEnemy {
    public:
    static const int BLOB_WIDTH = 30;
    static const int BLOB_HEIGHT = 30;
    static const int MAX_SPEED = 2;
    static const int DAMAGE = 1;

    MenacingBlob(int x, int y, Observer* observer);
    ~MenacingBlob();

    void move(uint32_t time) override;
};

#endif