#ifndef _GAME_H_
#define _GAME_H_

#include <vector>
#include <SDL2/SDL.h>

class Player;
class AbstractEntity;
class AbstractEnemy;
class Wall;
class Laser;
class View;
class Timer;

class Game {
    View* view;
    Timer* timer;
    Player* mPlayer;
    std::vector<Wall*> walls;
    std::vector<AbstractEnemy*> enemies;
    std::vector<Laser*> lasers;
    std::string levelPath;
    int levelWidth;
    int levelHeight;
    uint32_t time = 0;
    uint8_t prevKeyState[SDL_NUM_SCANCODES];

    int checkCollision(SDL_Rect hitBox1, SDL_Rect hitBox2);
    void handlePlayerEnemyCollision(Player* player, int collision);
    void handleEntityWallCollision(AbstractEntity* entity, Wall* wall, int collision);
    void respawnEnemies();

    public:
    Game(View* view);
    ~Game();

    void handleEvent(SDL_Event& event);
    void moveEntities();
    void initLevel(std::string path);

    SDL_Point getFocus();
    SDL_Point getMax();
};

#endif