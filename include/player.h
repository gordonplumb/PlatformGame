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

    void move() override;

    void render() override;

    static bool init(TextureWrapper* texture);

    Laser* fireLaser();

    private:
    static TextureWrapper* TEXTURE;
    static SDL_Rect PLAYER_CLIPS[];
};


#endif