#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <view.h>
#include <game.h>

using namespace std;

View* view;

void close() {
    delete view;
    SDL_Quit();
}

int main(int argc, char** argv) {
    view = new View();
    if (!view->init()) {
        cerr << "Failed to initialize" << endl;
    } else {
        bool quit = false;
        SDL_Event event;
        Game* game = new Game(view);
        game->initLevel("levels/temp");

        while (!quit) {
            while (SDL_PollEvent(&event) != 0) {
                if (event.type == SDL_QUIT) {
                    quit = true;
                }
                game->handleEvent(event);
            }
            game->moveEntities();
        }
    }

    // destroy window
    close();

    return 0;
}