#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SDL2/SDL.h>
#include <abstractentity.h>

class TextureWrapper;
class Laser;

class Player: public AbstractEntity {
    public:
    static const int PLAYER_WIDTH;
    static const int PLAYER_HEIGHT;
    static const int PLAYER_MAX_SPEED;
    static const int PLAYER_WALKING_FRAMES;

    Player();

    ~Player();

    void handleEvent(SDL_Event& event);

    void move(int top, int bot, int right, int left) override;

    void render(int camX, int camY) override;

    static bool init(TextureWrapper* texture, int textureHeight,
                     int textureWidth);

    Laser* fireLaser();

    private:
    static TextureWrapper* TEXTURE;
    static int TEXTURE_WIDTH;
    static int TEXTURE_HEIGHT;
    static SDL_Rect PLAYER_CLIPS[];
};


#endif