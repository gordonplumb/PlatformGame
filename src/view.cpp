#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <view.h>
#include <SDL2/SDL.h>
#include <gameconstants.h>
#include <texturewrapper.h>
#include <observer.h>
#include <wall.h>

using namespace std;

View::View() {}

View::~View() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

TextureWrapper* View::loadTexture(string path, int height, int width) {
    TextureWrapper* textureWrapper = new TextureWrapper();
    textureWrapper->init(path, renderer, height, width);

    return textureWrapper;
}

void View::loadTextures() {
    textures.emplace(PLAYER_ID, loadTexture("media/player.bmp", 90, 50));
    textures.emplace(LASER_ID, loadTexture("media/laser20x8.bmp"));
    textures.emplace(WALL_ID, loadTexture("media/wall.bmp"));
    textures.emplace(MEN_BLOB_ID, loadTexture("media/menacingblob.bmp", 30, 30));
}

bool View::init() {
    bool success = false;

    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        cerr << "SDL could not initialize, SDL_Error " << SDL_GetError() << endl;
    } else {
        window = SDL_CreateWindow("tbdGame", SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (window == nullptr) {
            cerr << "Window could not be created, SDL_Error " << SDL_GetError() << endl;
        } else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            if (renderer == nullptr) {
                cerr << "Renderer could not be created, SDL Error: ";
                cerr << SDL_GetError() << endl;
            } else {
                SDL_SetRenderDrawColor(renderer, 192, 192, 192, SDL_ALPHA_OPAQUE);
                loadTextures();

                camera = new SDL_Rect {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

                success = true;
            }
        }
    }

    return success;
}

void View::render(vector<Wall*> walls) {
    TextureWrapper* wallTexture = textures[WALL_ID];
    for (Wall* wall : walls) {
        SDL_Rect rect = wall->getHitBox();
        int DIM = 50;
        for (int i = 0; i < rect.h / DIM; i++) {
            for (int j = 0; j < rect.w / DIM; j++) {
                wallTexture->render(renderer, rect.x + j * DIM,
                                    rect.y + i * DIM, camera->x, camera->y);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

void View::clearRenderer() {
    SDL_RenderClear(renderer);
}

Observer* View::createObserver(int id, int maxWalkFrame, int xOffset, int yOffset) {
    Observer* observer = new Observer(id, this, textures[id], maxWalkFrame,
                                      xOffset, yOffset);
    observers.emplace_back(observer);
    
    return observer;
}

void View::removeObserver(Observer* observer) {
    observers.erase(remove(observers.begin(), observers.end(), observer),
                    observers.end());
}

void View::updateCamera(SDL_Point* point) {
    camera->x = point->x - SCREEN_WIDTH / 2;
    camera->y = point->y - SCREEN_HEIGHT / 2;

    if (camera->x < 0) {
        camera->x = 0;
    } else if (camera->x > max->x - camera->w) {
        camera->x = max->x - camera->w;
    }
    if (camera->y < 0) {
        camera->y = 0;
    } else if (camera->y > max->y - camera->h) {
        camera->y = max->y - camera->h;
    }
}

void View::setMax(SDL_Point* max) {
    this->max = max;
}

SDL_Renderer* View::getRenderer() {
    return renderer;
}

SDL_Rect* View::getCamera() {
    return camera;
}
