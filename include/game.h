#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include <SDL2/SDL.h>

class Player;
class AbstractEntity;
class AbstractEnemy;
class Wall;
class Laser;
class View;
class Timer;

class Game {
    std::shared_ptr<View> view;
    std::unique_ptr<Timer> timer;
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Wall>> walls;
    std::vector<std::unique_ptr<AbstractEnemy>> enemies;
    std::vector<std::unique_ptr<Laser>> lasers;
    SDL_Rect goal;
    SDL_Point spawn;
    int levelIndex = 0;
    int levelWidth;
    int levelHeight;
    uint32_t time = 0;

    // collision handling
    int checkCollision(SDL_Rect hitBox1, SDL_Rect hitBox2);
    void handlePlayerEnemyCollision(Player& player, int collision, int damage);
    void handleEntityWallCollision(AbstractEntity& entity, Wall& wall,
        int collision);
    void handlePlayerBorderCollision(Player& player);
    void handleCharacterBorderCollision(AbstractEntity& entity);

    // update helpers
    void moveEntities();
    bool levelCleared();
    void renderGame(bool dead, bool clear, bool win);

    public:
    Game();
    ~Game();
    bool init();

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