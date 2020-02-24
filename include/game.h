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

    int checkCollision(SDL_Rect hitBox1, SDL_Rect hitBox2);
    void handlePlayerEnemyCollision(Player* player, int collision);
    void handleEntityWallCollision(AbstractEntity* entity, Wall* wall,
        int collision);
    void handleCharacterBorderCollision(AbstractEntity* entity);

    void moveEntities();
    void render();

    public:
    Game(View* view);
    ~Game();

    void initLevel(std::string path);

    // player action functions
    void playerJump();
    void playerLookUp(bool isLookingUp);
    void playerCrouch(bool isCrouching, bool left, bool right);
    void playerMove(bool stop, bool forward);
    void playerShoot();
    void resetPlayerActions(bool left, bool right, bool up, bool down);

    // move game state along and render to view
    void update();

    void respawnEnemies();

    // timer functions
    void pause();
    void unpause();
    bool isPaused();
};

#endif