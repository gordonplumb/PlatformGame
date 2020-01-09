#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <texturewrapper.h>
#include <game.h>
#include <level.h>
#include <wall.h>
#include <player.h>
#include <menacingblob.h>
#include <laser.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

// move this to view class eventually
TextureWrapper gPlayerSprite;
TextureWrapper gMenacingBlobSprite;
TextureWrapper gTexture;
TextureWrapper gWall;
TextureWrapper gLaser;

bool init() {
    bool success = true;

    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        cerr << "SDL could not initialize, SDL_Error " << SDL_GetError() << endl;
        success = false;
    } else {
        gWindow = SDL_CreateWindow("tbdGame", SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (gWindow == NULL) {
            cerr << "Window could not be created, SDL_Error " << SDL_GetError() << endl;
            success = false;
        } else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            if (gRenderer == NULL) {
                cerr << "Renderer could not be created, SDL Error: ";
                cerr << SDL_GetError() << endl;
            } else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            }

            // gSurface = SDL_GetWindowSurface( gWindow );
            // SDL_FillRect( gSurface, NULL, SDL_MapRGB( gSurface->format, 0xFF, 0xFF, 0xFF ) );
            // SDL_UpdateWindowSurface( gWindow );
        }
    }

    return success;
}

bool initMedia() {
    bool success = true;

    if (!Player::init(&gPlayerSprite)) {
        cerr << "Player init failed" << endl;
        success = false;
    }

    if (!MenacingBlob::init(&gMenacingBlobSprite)) {
        cerr << "Menacing blob init failed" << endl;
        success = false;
    }

    if (!Wall::init(&gWall, 50)) {
        cerr << "Wall init failed" << endl;
        success = false;
    }

    if (!Laser::init(&gLaser)) {
        cerr << "Laser init failed" << endl;
        success = false;
    }

    return success;
}

// load a single image
// SDL_Surface* loadSurface( string path ) {
//     SDL_Surface* optimizedSurface = NULL;
//     SDL_Surface* surface = SDL_LoadBMP( path.c_str() );

//     if( surface == NULL ) {
//         cerr << "Unable to load image " << path << ", SDL Error: ";
//         cerr << SDL_GetError() << endl;
//     } else {
//         optimizedSurface = SDL_ConvertSurface( surface, gSurface->format, 0 );

//         if( optimizedSurface == NULL ) {
//             cerr << "Unable to optimize image " << path << ", SDL Error: ";
//             cerr << SDL_GetError() << endl;
//         }

//         SDL_FreeSurface( surface );
//     }

//     return optimizedSurface;
// }

SDL_Texture* loadTexture(string path) {
    SDL_Texture* texture = NULL;

    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    if (surface == NULL) {
        cerr << "Unable to load " << path << ", SDL Error: " << SDL_GetError() << endl;
    }
    texture = SDL_CreateTextureFromSurface(gRenderer, surface);

    if (texture == NULL) {
        cerr << "Unable to create texture from " << path << ", SDL Error: ";
        cerr << SDL_GetError() << endl;
    }

    SDL_FreeSurface(surface);

    return texture;
}

bool loadMedia() {
    bool success = true;

    if (!gPlayerSprite.loadTexture("media/player.bmp")) {
        cerr << "Unable to load player sprite, SDL Error: " << SDL_GetError() << endl;
        success = false;
    }

    if (!gMenacingBlobSprite.loadTexture("media/menacingblob.bmp")) {
        cerr << "Unable to load enemy1 sprite, SDL Error: " << SDL_GetError() << endl;
        success = false;
    }

    if (!gTexture.loadTexture("media/background1.bmp")) {
        cerr << "Failed to load background1" << endl;
        success = false;
    }

    if (!gWall.loadTexture("media/wall.bmp")) {
        cerr << "Failed to load wall texture" << endl;
        success = false;
    }

    if (!gLaser.loadTexture("media/laser20x8.bmp")) {
        cerr << "Failed to load laser texture" << endl;
        success = false;
    }

    return success;
}

void close() {
    gPlayerSprite.free();
    gMenacingBlobSprite.free();
    gTexture.free();

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;

    SDL_Quit();
}

int main(int argc, char** argv) {
    if (!init()) {
        cerr << "Failed to initialize" << endl;
    } else {
        if(!loadMedia()) {
            cerr << "Failed to load media" << endl;
        } else {
            if (initMedia()) {
                bool quit = false;
                SDL_Event event;

                Game* game = new Game();
                game->init();
                Level* level = new Level("levels/temp");
                level->init();
                game->setLevel(level);

                while (!quit) {
                    while (SDL_PollEvent(&event) != 0) {
                        if (event.type == SDL_QUIT) {
                            quit = true;
                        }
                        game->handleEvent(event);
                    }

                    game->moveEntities();

                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderClear(gRenderer);

                    gTexture.render(0, 0);
                    game->render();

                    SDL_RenderPresent(gRenderer);
                }
            }
            
        }
    }

    // destroy window
    close();

    return 0;
}