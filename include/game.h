#ifndef _GAME_H_
#define _GAME_H_

#include <vector>
#include <SDL2/SDL.h>

class Player;
class AbstractEntity;
class Wall;
class Level;

class Game {
    Player* mPlayer;
    // std::vector<AbstractEnemy*> mEnemies;
    Level* mLevel;

    int checkCollision(SDL_Rect hitBox1, SDL_Rect hitBox2);
    void handlePlayerEnemyCollision(Player* player, int collision);
    void handleEntityWallCollision(AbstractEntity* entity, Wall* wall, int collision);

    public:
    bool init();
    void handleEvent(SDL_Event& event);
    void moveEntities();
    void render();
    void setLevel(Level* level);
};

#endif