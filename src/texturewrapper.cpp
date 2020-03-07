#include <string>
#include <iostream>
#include <texturewrapper.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

TextureWrapper::TextureWrapper() {
    texture = nullptr;
    width = 0;
    height = 0;
}

TextureWrapper::~TextureWrapper() {
    free();
}

bool TextureWrapper::init(string path, SDL_Renderer* renderer,
    int clipHeight, int clipWidth) {
    free();

    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    if (surface == nullptr) {
        cerr << "Unable to load " << path << ", " << SDL_GetError() << endl;
    } else {
        SDL_SetColorKey(surface, SDL_TRUE,
            SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
        texture = SDL_CreateTextureFromSurface(renderer, surface);

        if (texture == nullptr) {
            cerr << "Unable to create texture from " << path << ", ";
            cerr << SDL_GetError() << endl;
        } else {
            width = surface->w;
            height = surface->h;
            
            // set clip width and height if they weren't provided
            if (clipHeight == 0) clipHeight = height;
            if (clipWidth == 0) clipWidth = width;

            // load clip dimensions
            int row = height / clipHeight;
            int col = width / clipWidth;
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    SDL_Rect* clip = new SDL_Rect {clipWidth * j,
                        clipHeight * i, clipWidth, clipHeight};
                    clips.emplace_back(clip);
                }
            }
        }

        SDL_FreeSurface(surface);
    }

    return texture != nullptr;
}

bool TextureWrapper::initFromText(std::string textureText, TTF_Font* font,
                                  SDL_Renderer* renderer, SDL_Color textColour) {
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(),
                                                    textColour);
    
    if (textSurface == nullptr) {
        cerr << "Unable to render text surface " << TTF_GetError() << endl;
    } else {
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);

        if (texture == nullptr) {
            cerr << "Failed to create texture from rendered text ";
            cerr << TTF_GetError() << endl;
        } else {
            width = textSurface->w;
            height = textSurface->h;
        }

        SDL_FreeSurface(textSurface);
    }

    return texture != nullptr;
}

void TextureWrapper::free() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        width = 0;
        height = 0;
    }
}

void TextureWrapper::render(SDL_Renderer* renderer, int x, int y, int camX,
                            int camY, SDL_Rect* clip, double angle,
                            SDL_Point* centre, SDL_RendererFlip flip) {
    SDL_Rect renderRect = {x - camX, y - camY, width, height};

    if (clip != nullptr) {
        renderRect.w = clip->w;
        renderRect.h = clip->h;
    }

    SDL_RenderCopyEx(renderer, texture, clip, &renderRect, angle, centre, flip);
}

void TextureWrapper::setColour(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(texture, red, green, blue);
}

SDL_Rect* TextureWrapper::getClip(int index) {
    return clips.at(index);
}
