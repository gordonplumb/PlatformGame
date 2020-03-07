#ifndef TIMER_H
#define TIMER_H

class Timer {
    uint32_t startTicks;
    uint32_t pausedTicks;

    bool started;
    bool paused;

    public:
    Timer();

    void start();
    void stop();
    void pause();
    void unpause();

    uint32_t getTicks();

    bool isStarted();
    bool isPaused();
};

#endif