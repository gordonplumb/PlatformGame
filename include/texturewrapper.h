#ifndef _TEXTURE_WRAPPER_H_
#define _TEXTURE_WRAPPER_H_

#include <string>
#include <SDL2/SDL.h>

class TextureWrapper {
    public:
    TextureWrapper();

    ~TextureWrapper();

    bool loadTexture( std::string path );

    void free();

    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0,
                 SDL_Point* centre = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    void setColour( Uint8 red, Uint8 green, Uint8 blue );

    int getWidth();

    int getHeight();

    private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};

#endif