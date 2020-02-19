#ifndef _TEXTURE_WRAPPER_H_
#define _TEXTURE_WRAPPER_H_

#include <string>
#include <vector>
#include <SDL2/SDL.h>

class TextureWrapper {
    SDL_Texture* mTexture;
    std::vector<SDL_Rect*> clips;
    int mWidth;
    int mHeight;

    public:
    TextureWrapper();

    ~TextureWrapper();

    bool init(std::string path, SDL_Renderer* renderer, int height = 0,
              int width = 0);

    void free();

    void render(SDL_Renderer* renderer, int x, int y, int camX, int camY, 
                SDL_Rect* clip = nullptr, double angle = 0.0, 
                SDL_Point* centre = nullptr,
                SDL_RendererFlip flip = SDL_FLIP_NONE);

    void setColour(Uint8 red, Uint8 green, Uint8 blue);

    int getWidth();

    int getHeight();

    SDL_Rect* getClip(int index);
};

#endif