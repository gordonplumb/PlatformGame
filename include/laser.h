#ifndef _LASER_
#define _LASER_

#include <abstractentity.h>

class TextureWrapper;

class Laser: public AbstractEntity {
    public:
    static const int LASER_WIDTH = 20;
    static const int LASER_HEIGHT = 5;
    static const int LASER_MAX_SPEED = 10;

    Laser(int x, int y, bool horizontal, bool vertical, int xModifier,
          int yModifier);
    ~Laser();

    void move(int top, int bot, int right, int left) override;
    void render(int camX, int camY) override;

    static bool init(TextureWrapper* texture);

    private:
    bool mHorizontal;
    bool mVertical;
    int mXModifier;
    int mYModifier;
    static TextureWrapper* TEXTURE;

};

#endif