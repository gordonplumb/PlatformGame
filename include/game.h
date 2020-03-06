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
    SDL_Rect goal;
    int levelIndex = 0;
    int levelWidth;
    int levelHeight;
    uint32_t time = 0;

    int checkCollision(SDL_Rect hitBox1, SDL_Rect hitBox2);
    void handlePlayerEnemyCollision(Player* player, int collision, int damage);
    void handleEntityWallCollision(AbstractEntity* entity, Wall* wall,
        int collision);
    void handleCharacterBorderCollision(AbstractEntity* entity);

    void moveEntities();
    bool levelCleared();
    void renderGame(bool dead, bool clear, bool win);

    public:
    Game(View* view);
    ~Game();

    void initLevel();

    // player action functions
    void playerJump();
    void playerLookUp(bool isLookingUp);
    void playerCrouch(bool isCrouching, bool left, bool right);
    void playerMove(bool stop, bool forward);
    void playerShoot();
    void playerDeath();
    void resetPlayerActions(bool left, bool right, bool up, bool down);

    // move game state along and render to view
    void update();

#ifdef DEBUG
    void respawnEnemies();
    void killPlayer();
#endif

    // timer functions
    void pause();
    void unpause();
    bool isPaused();
    bool isStarted();
};

#endif