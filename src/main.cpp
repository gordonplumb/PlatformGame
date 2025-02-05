#include <SDL2/SDL.h>
#include <memory>
#include <iostream>
#include <string>
#include <view.h>
#include <game.h>

using namespace std;

unique_ptr<Game> game;
uint8_t prevKeyState[SDL_NUM_SCANCODES];

bool handleEvent(SDL_Event& event) {
    const uint8_t* state = SDL_GetKeyboardState(nullptr);
    bool wasPaused = false;

    if (state[SDL_SCANCODE_Q] == 1) {
        return false;
    }
    if (game->isPaused()) {
        // unpause
        if (state[SDL_SCANCODE_P] == 1 && prevKeyState[SDL_SCANCODE_P] == 0) {
            game->unpause();
            wasPaused = true;
        }
    } else if (!game->isStarted()) {
        if (state[SDL_SCANCODE_SPACE] == 1
            && prevKeyState[SDL_SCANCODE_SPACE] == 0) {
            game->initLevel();
            wasPaused = true;
        }
    } else {
        // pause
        if (state[SDL_SCANCODE_P] == 1 && prevKeyState[SDL_SCANCODE_P] == 0) {
            game->pause();
            // resetting all actions that result from a held key 
            game->resetPlayerActions(
                state[SDL_SCANCODE_LEFT] == 1 && prevKeyState[SDL_SCANCODE_LEFT],
                state[SDL_SCANCODE_RIGHT] == 1 && prevKeyState[SDL_SCANCODE_RIGHT],
                state[SDL_SCANCODE_UP] == 1,
                state[SDL_SCANCODE_DOWN] == 1
            );
        }

        // jump
        if (state[SDL_SCANCODE_SPACE] == 1
            && prevKeyState[SDL_SCANCODE_SPACE] == 0) {
            game->playerJump();
        }

        // look up
        if (state[SDL_SCANCODE_UP] == 1 && prevKeyState[SDL_SCANCODE_UP] == 0) {
            game->playerLookUp(true);
        } else if (state[SDL_SCANCODE_UP] == 0 && prevKeyState[SDL_SCANCODE_UP] == 1) {
            game->playerLookUp(false);
        }

        // crouch
        if (state[SDL_SCANCODE_DOWN] == 1
            && prevKeyState[SDL_SCANCODE_DOWN] == 0) {
            game->playerCrouch(
                true,
                prevKeyState[SDL_SCANCODE_LEFT] == 1,
                prevKeyState[SDL_SCANCODE_RIGHT] == 1
            );
        } else if (state[SDL_SCANCODE_DOWN] == 0
            && prevKeyState[SDL_SCANCODE_DOWN] == 1) {
            game->playerCrouch(
                false,
                prevKeyState[SDL_SCANCODE_LEFT] == 1,
                prevKeyState[SDL_SCANCODE_RIGHT] == 1
            );
        }

        // left
        bool left;
        if (state[SDL_SCANCODE_LEFT] == 1 && prevKeyState[SDL_SCANCODE_LEFT] == 0) {
            game->playerMove(false, false);
        } else if (state[SDL_SCANCODE_LEFT] == 0
            && prevKeyState[SDL_SCANCODE_LEFT] == 1) {
            game->playerMove(true, false);
        }

        // right
        if (state[SDL_SCANCODE_RIGHT] == 1
            && prevKeyState[SDL_SCANCODE_RIGHT] == 0) {
            game->playerMove(false, true);
        } else if (state[SDL_SCANCODE_RIGHT] == 0
            && prevKeyState[SDL_SCANCODE_RIGHT] == 1) {
            game->playerMove(true, true);
        }

        // laser
        if (state[SDL_SCANCODE_Z] == 1 && prevKeyState[SDL_SCANCODE_Z] == 0) {
            game->playerShoot();
        }
#ifdef DEBUG
        if (state[SDL_SCANCODE_R] == 1 && prevKeyState[SDL_SCANCODE_R] == 0) {
            game->respawnEnemies();
        }

        if (state[SDL_SCANCODE_K] == 1 && prevKeyState[SDL_SCANCODE_K] == 0) {
            game->killPlayer();
        }
#endif
    }

    // update previous key state
    memcpy(prevKeyState, state, sizeof(uint8_t) * SDL_NUM_SCANCODES);
    if (wasPaused) {
        // set the key state for held key actions to 0 so next handleEvent call
        // will pick them up as new key presses
        prevKeyState[SDL_SCANCODE_UP] = 0;
        prevKeyState[SDL_SCANCODE_DOWN] = 0;
        prevKeyState[SDL_SCANCODE_LEFT] = 0;
        prevKeyState[SDL_SCANCODE_RIGHT] = 0;
    }

    return true;
}

int main(int argc, char** argv) {
    game = make_unique<Game>();
    if (!game->init()) {
        cerr << "Failed to initialize" << endl;
    } else {
        bool quit = false;
        SDL_Event event;
        memset(prevKeyState, 0, sizeof(uint8_t) * SDL_NUM_SCANCODES);
        game->initLevel();

        while (!quit) {
            while (SDL_PollEvent(&event) != 0) {
                if (event.type == SDL_QUIT || !handleEvent(event)) {
                    quit = true;
                }
            }
            game->update();
        }
    }

    return 0;
}