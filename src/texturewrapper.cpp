#include <string>
#include <iostream>
#include <texturewrapper.h>
#include <SDL2/SDL.h>

using namespace std;

TextureWrapper::TextureWrapper() {
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

TextureWrapper::~TextureWrapper() {
    free();
}

bool TextureWrapper::init(string path, SDL_Renderer* renderer,
                          int height, int width) {
    free();
    SDL_Texture* texture = nullptr;

    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    if (surface == nullptr) {
        cerr << "Unable to load " << path << ", SDL Error: " << SDL_GetError() << endl;
    } else {
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
        texture = SDL_CreateTextureFromSurface(renderer, surface);

        if (texture == nullptr) {
            cerr << "Unable to create texture from " << path << ", SDL Error: ";
            cerr << SDL_GetError() << endl;
        } else {
            mWidth = surface->w;
            mHeight = surface->h;
            
            // set clip width and height if they weren't provided
            if (height == 0) height = mHeight;
            if (width == 0) width = mWidth;

            // load clip dimensions
            int row = mHeight / height;
            int col = mWidth / width;
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    SDL_Rect* clip = new SDL_Rect {width * j, height * i, width, height};
                    clips.emplace_back(clip);
                }
            }
        }

        SDL_FreeSurface(surface);
    }

    mTexture = texture;
    return texture != nullptr;
}

void TextureWrapper::free() {
    if (mTexture != nullptr) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

void TextureWrapper::render(SDL_Renderer* renderer, int x, int y, int camX,
                            int camY, SDL_Rect* clip, double angle,
                            SDL_Point* centre, SDL_RendererFlip flip) {
    SDL_Rect renderRect = {x - camX, y - camY, mWidth, mHeight};

    if (clip != nullptr) {
        renderRect.w = clip->w;
        renderRect.h = clip->h;
    }

    SDL_RenderCopyEx(renderer, mTexture, clip, &renderRect, angle, centre, flip);
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

SDL_Rect* TextureWrapper::getClip(int index) {
    return clips.at(index);
}
