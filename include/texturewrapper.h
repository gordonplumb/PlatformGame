#ifndef TEXTUREWRAPPER_H
#define TEXTUREWRAPPER_H

#include <string>
#include <vector>
#include <SDL2/SDL.h>

typedef struct _TTF_Font TTF_Font;

class TextureWrapper {
    SDL_Texture* texture;
    std::vector<SDL_Rect*> clips;
    int width;
    int height;

    public:
    TextureWrapper();

    ~TextureWrapper();

    bool init(std::string path, SDL_Renderer* renderer, int clipHeight = 0,
        int clipWidth = 0);

    bool initFromText(std::string textureText, TTF_Font* font,
        SDL_Renderer* renderer, SDL_Color textColour);

    void free();

    void render(SDL_Renderer* renderer, int x, int y, int camX, int camY, 
        SDL_Rect* clip = nullptr, double angle = 0.0, 
        SDL_Point* centre = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void setColour(Uint8 red, Uint8 green, Uint8 blue);

    SDL_Rect* getClip(int index);
};

#endif