#ifndef _TIMER_
#define _TIMER_

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