#include <texturewrapper.h>
#include <SDL2/SDL.h>
#include <string>
#include <iostream>

using namespace std;

// this works but isn't right
extern SDL_Renderer* gRenderer;

TextureWrapper::TextureWrapper() {
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

TextureWrapper::~TextureWrapper() {
    free();
}

bool TextureWrapper::loadTexture(string path) {
    free();
    SDL_Texture* texture = nullptr;

    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    if (surface == nullptr) {
        cerr << "Unable to load " << path << ", SDL Error: " << SDL_GetError() << endl;
    } else {
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
        texture = SDL_CreateTextureFromSurface(gRenderer, surface);

        if (texture == nullptr) {
            cerr << "Unable to create texture from " << path << ", SDL Error: ";
            cerr << SDL_GetError() << endl;
        } else {
            mWidth = surface->w;
            mHeight = surface->h;
        }

        SDL_FreeSurface(surface);
    }

    mTexture = texture;
    return texture != nullptr;
}

void TextureWrapper::free() {
    if(mTexture != nullptr) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

void TextureWrapper::render(int x, int y, int camX, int camY, SDL_Rect* clip, double angle,
                            SDL_Point* centre, SDL_RendererFlip flip) {
    SDL_Rect renderRect = {x - camX, y - camY, mWidth, mHeight};

    if (clip != nullptr) {
        renderRect.w = clip->w;
        renderRect.h = clip->h;
    }

    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderRect, angle, centre, flip);
}

void TextureWrapper::setColour(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

int TextureWrapper::getWidth() {
    return mWidth;
}

int TextureWrapper::getHeight() {
    return mHeight;
}
