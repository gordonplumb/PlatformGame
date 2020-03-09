#ifndef GAMECONSTANTS_H
#define GAMECONSTANTS_H

#include <string>

// screen dimensions
const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;

// entity ids
const int PLAYER_ID = 0;
const int LASER_ID = 1;
const int WALL_ID = 5;
const int GOAL_ID = 6;
const int MEN_BLOB_ID = 10;
const int ALIEN_ID = 11;
const int BEE_ID = 12;

// other ids
const int HEART_ID = 20;
const int TIMER_ID = 21;
const int GAME_OVER_ID = 22;
const int LEVEL_CLEAR_ID = 23;
const int YOU_WIN_ID = 24;

// level specs
const std::string LEVEL_PATHS[] = {
    "levels/noenemies",
    "levels/temp"
};
const int NUM_LEVELS = 2;

// player

// game strings
const std::string GAME_OVER = "Game Over";
const std::string LEVEL_CLEAR = "Level Cleared! Press space to continue";
const std::string YOU_WIN = "You Win!";

#endif