#ifndef _LASER_
#define _LASER_

#include <abstractentity.h>

class TextureWrapper;

class Laser: public AbstractEntity {
    public:
    static const int LASER_WIDTH = 20;
    static const int LASER_HEIGHT = 5;
    static const int LASER_MAX_SPEED = 4;

    Laser(int x, int y, int xModifier, int yModifier);
    ~Laser();

    void move() override;
    void render() override;

    static bool init(TextureWrapper* texture);

    private:
    int xModifier;
    int yModifier;
    static TextureWrapper* TEXTURE;

};

#endif