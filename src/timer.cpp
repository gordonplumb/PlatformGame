#include <SDL2/SDL_timer.h>
#include <timer.h>

Timer::Timer() {
    stop();
}

void Timer::start() {
    started = true;
    paused = false;
    startTicks = SDL_GetTicks();
    pausedTicks = 0;
}

void Timer::stop() {
    started = false;
    paused = false;
    startTicks = 0;
    pausedTicks = 0;
}

void Timer::pause() {
    if (started && !paused) {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
}

void Timer::unpause() {
    if (started && paused) {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

uint32_t Timer::getTicks() {
    uint32_t time = 0;

    if (started && paused) {
        time = pausedTicks;
    } else if (started) {
        time = SDL_GetTicks() - startTicks;
    }

    return time;
}

bool Timer::isStarted() {
    return started;
}

bool Timer::isPaused() {
    return paused;
}