#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <view.h>
#include <gameconstants.h>
#include <texturewrapper.h>
#include <observer.h>
#include <movingobserver.h>
#include <playerstatusobserver.h>
#include <wall.h>

using namespace std;

View::View() {}

View::~View() {
    for (auto const& pair : textures) {
        pair.second->free();
    }
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

shared_ptr<View> View::getSharedPtr() {
    return shared_from_this();
}

shared_ptr<TextureWrapper> View::loadTexture(string path, int height,
    int width) {
    shared_ptr<TextureWrapper> textureWrapper = make_shared<TextureWrapper>();
    textureWrapper->init(path, renderer, height, width);

    return textureWrapper;
}

shared_ptr<TextureWrapper> View::loadTextureFromText(string text) {
    shared_ptr<TextureWrapper> textureWrapper = make_shared<TextureWrapper>();
    textureWrapper->initFromText(text, font, renderer, fontColour);

    return textureWrapper;
}

void View::loadTextures() {
    textures.emplace(PLAYER_ID, loadTexture("media/player.bmp", 72, 44));
    textures.emplace(LASER_ID, loadTexture("media/laser20x8.bmp"));
    textures.emplace(WALL_ID, loadTexture("media/wall.bmp"));
    textures.emplace(GOAL_ID, loadTexture("media/goal.bmp"));
    textures.emplace(MEN_BLOB_ID, loadTexture("media/menacingblob.bmp", 30, 30));
    textures.emplace(ALIEN_ID, loadTexture("media/alien.bmp", 70, 20));
    textures.emplace(BEE_ID, loadTexture("media/bee.bmp", 20, 30));
    textures.emplace(HEART_ID, loadTexture("media/heart.bmp"));

    textures.emplace(TIMER_ID, loadTextureFromText("0"));
    textures.emplace(GAME_OVER_ID, loadTextureFromText(GAME_OVER));
    textures.emplace(LEVEL_CLEAR_ID, loadTextureFromText(LEVEL_CLEAR));
    textures.emplace(YOU_WIN_ID, loadTextureFromText(YOU_WIN));
}

bool View::init() {
    bool success = false;

    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        cerr << "SDL failed to initialize " << SDL_GetError() << endl;
    } else if (TTF_Init() == -1) {
        cerr << "TTF failed to initialize " << TTF_GetError() << endl;
    } else {
        // initialization of SDL and TTF libraries completed
        window = SDL_CreateWindow("tbdGame", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);

        if (window == nullptr) {
            cerr << "Window could not be created " << SDL_GetError() << endl;
        } else {
            renderer = SDL_CreateRenderer(window, -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            // load the font with point size 20
            font = TTF_OpenFont("media/OpenSans-Regular.ttf", 20);

            if (renderer == nullptr) {
                cerr << "Renderer was not created "<< SDL_GetError() << endl;
            } else if (font == nullptr) {
                cerr << "Font was not created " << TTF_GetError() << endl;
            } else {
                // set colours for screen and font
                SDL_SetRenderDrawColor(renderer, 192, 192, 192,
                    SDL_ALPHA_OPAQUE);
                fontColour = {0, 0, 0};

                // construct the camera for scrolling
                camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
                
                loadTextures();

                success = true;
            }
        }
    }

    return success;
}


void View::renderTerrain(vector<unique_ptr<Wall>>& walls, SDL_Rect goal) {
    // render walls
    shared_ptr<TextureWrapper> wallTexture = textures[WALL_ID];
    for (auto& wall : walls) {
        SDL_Rect rect = wall->getHitBox();
        int DIM = 25;
        for (int i = 0; i < rect.h / DIM; i++) {
            for (int j = 0; j < rect.w / DIM; j++) {
                wallTexture->render(renderer, rect.x + j * DIM,
                    rect.y + i * DIM, camera.x, camera.y);
            }
        }
    }

    // render goal
    textures[GOAL_ID]->render(renderer, goal.x, goal.y, camera.x, camera.y);
}

void View::renderStatusText(bool gameOver, bool levelClear, bool win) {
    textures[TIMER_ID]->render(renderer, SCREEN_WIDTH - 45, 5, 0, 0);
    if (win) {
        textures[YOU_WIN_ID]->render(renderer, SCREEN_WIDTH / 2 - 30,
        (SCREEN_HEIGHT - 20) / 2, 0, 0);
    } else if (levelClear) {
        textures[LEVEL_CLEAR_ID]->render(renderer, SCREEN_WIDTH / 2 - 160,
        (SCREEN_HEIGHT - 20) / 2, 0, 0);
    } else if (gameOver) {
        textures[GAME_OVER_ID]->render(renderer, SCREEN_WIDTH / 2 - 40,
        (SCREEN_HEIGHT - 20) / 2, 0, 0);
    }
    SDL_RenderPresent(renderer);
}


void View::clearRenderer() {
    SDL_RenderClear(renderer);
}

unique_ptr<Observer> View::createMovingObserver(int id, int maxWalkFrame, int xOffset,
    int yOffset) {
    unique_ptr<Observer> observer = make_unique<MovingObserver>(id,
        getSharedPtr(), textures[id], maxWalkFrame, xOffset, yOffset);
    
    return observer;
}

unique_ptr<Observer> View::createPlayerStatusObserver() {
    unique_ptr<Observer> observer = make_unique<PlayerStatusObserver>(
        getSharedPtr(), textures[HEART_ID]);

    return observer;
}

void View::updateCamera(SDL_Point point) {
    camera.x = point.x - SCREEN_WIDTH / 2;
    camera.y = point.y - SCREEN_HEIGHT / 2;

    if (camera.x < 0) {
        camera.x = 0;
    } else if (camera.x > max.x - camera.w) {
        camera.x = max.x - camera.w;
    }
    if (camera.y < 0) {
        camera.y = 0;
    } else if (camera.y > max.y - camera.h) {
        camera.y = max.y - camera.h;
    }
}

void View::setMax(int x, int y) {
    this->max = {x, y};
}

void View::updateTime(Uint32 time) {
    timeText.str("");
    timeText << time;
    textures[TIMER_ID]->initFromText(timeText.str(), font, renderer,
        fontColour);
}

SDL_Renderer* View::getRenderer() {
    return renderer;
}

SDL_Rect View::getCamera() {
    return camera;
}
