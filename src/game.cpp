#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <game.h>
#include <view.h>
#include <timer.h>
#include <gameconstants.h>
#include <wall.h>
#include <player.h>
#include <menacingblob.h>
#include <alien.h>
#include <bee.h>
#include <movementstrategy.h>
#include <patrolstrategy.h>
#include <followplayerstrategy.h>
#include <laser.h>

using namespace std;

const int RIGHT = 1;
const int LEFT = 2;
const int TOP = 4;
const int BOTTOM = 8;

Game::Game() {}
Game::~Game() {}

bool Game::init() {
    view = make_shared<View>();
    if (!view->init()) {
        return false;
    } else {
        timer = make_unique<Timer>();
        player = make_unique<Player>(
            view->createMovingObserver(PLAYER_ID, 3)
        );
        player->addObserver(view->createPlayerStatusObserver());

        return true;
    }
}

void Game::playerJump() {
    if (player->getJump() && !player->isCrouching()) {
        player->changeVelY(-15);
        player->setJump(false);
    }
}

void Game::playerLookUp(bool isLookingUp) {
    player->setLookingUp(isLookingUp);
}

void Game::playerCrouch(bool isCrouching, bool left, bool right) {
    if (isCrouching) {
        if (left) {
            player->changeVelX(Player::PLAYER_MAX_SPEED);
        }
        if (right) {
            player->changeVelX(Player::PLAYER_MAX_SPEED * -1);
        }
    } else {
        if (left) {
            player->changeVelX(Player::PLAYER_MAX_SPEED * -1);
        }
        if (right) {
            player->changeVelX(Player::PLAYER_MAX_SPEED);
        }
    }
    player->setCrouch(isCrouching);
}

void Game::playerMove(bool stop, bool forward) {
    int multiplier = forward ? 1 : -1;
    if (stop) {
        multiplier *= -1;
    }
    if (!player->isCrouching()) {
        player->changeVelX(Player::PLAYER_MAX_SPEED * multiplier);
    }
}

void Game::playerShoot() {
    bool horizontal, vertical;
    int x, y;
    bool forward = player->isForward();
    bool lookingUp = player->isLookingUp();
    int xModifier = forward ? 1 : -1;
    int yModifier = lookingUp ? -1 : 1;
    SDL_Rect hitbox = player->getHitBox();

    if (player->isCrouching()) {
        horizontal = true;
        vertical = false;
        x = hitbox.x + (forward ? 31 : -10);
        y = hitbox.y + 49;
    } else if (lookingUp) {
        if (player->getVelX() == 0) {
            x = hitbox.x + (forward ? 40 : 15);
            y = hitbox.y;
        } else {
            x = hitbox.x + (forward ? 36 : -6);
            y = hitbox.y + (forward ? 17 : 5);
            horizontal = true;
        }
        vertical = true;
    } else {
        horizontal = true;
        vertical = false;
        x = hitbox.x + (forward ? 37 : -17);
        y = hitbox.y + 36;
    }

    lasers.push_back(make_unique<Laser>(x, y, horizontal, vertical, xModifier,
        yModifier, 1, view->createMovingObserver(LASER_ID, 0)));
}

void Game::playerDeath() {
    timer->stop();
}

void Game::resetPlayerActions(bool left, bool right, bool up, bool down) {
    // resetting all actions that result from a held key 
    if (left) {
        if (!player->isCrouching()) {
            player->changeVelX(Player::PLAYER_MAX_SPEED);
        }
    }
    if (right) {
        if (!player->isCrouching()) {
            player->changeVelX(Player::PLAYER_MAX_SPEED * -1);
        }
    }
    if (up) {
        player->setLookingUp(false);
    }
    if (down) {
        player->setCrouch(false);
    }
}

void Game::update() {
    if (!(isPaused() || !isStarted())) {
        moveEntities();
        bool clear = levelCleared();
        renderGame(player->getHP() <= 0, clear, levelIndex == NUM_LEVELS);
    }
}

void Game::handlePlayerBorderCollision(Player& player) {
    SDL_Rect hitbox = player.getHitBox();
    if (hitbox.x < 0) {
        player.changePosX(hitbox.x * -1 + 1);
    } else if (hitbox.x + hitbox.w > levelWidth) {
        int collisionDepth = levelWidth - hitbox.x - hitbox.w - 1;
        player.changePosX(collisionDepth);
    }

    if (hitbox.y < 0) {
        player.changePosY(hitbox.y * -1 + 1);
    } else if (hitbox.y > levelHeight) {
        player.changeHP(-1);
        player.setInvincibility(true, timer->getTicks());
        player.changeVelY(player.getVelY() * -1);
        player.setPos(spawn.x, spawn.y);
    }
}

void Game::handleCharacterBorderCollision(AbstractEntity& entity) {
    SDL_Rect hitbox = entity.getHitBox();

    if (hitbox.x < 0) {
        entity.changePosX(hitbox.x * -1 + 1);
    } else if (hitbox.x + hitbox.w > levelWidth) {
        int collisionDepth = levelWidth - hitbox.x - hitbox.w - 1;
        entity.changePosX(collisionDepth);
    }

    if (hitbox.y < 0) {
        entity.changePosY(hitbox.y * -1 + 1);
    } else if (hitbox.y > levelHeight) {
        entity.changeHP(entity.getHP() * -1);
    }
}

void Game::moveEntities() {
    // update time
    Uint32 elapsed = timer->getTicks();
    if (elapsed >= time + 1000) {
        time = elapsed;
        view->updateTime(time / 1000);
    }

    // move characters first
    player->move(elapsed);
    handlePlayerBorderCollision(*player);
    for (auto& enemy : enemies) {
        enemy->move(player->getHitBox().x, player->getHitBox().y);
        handleCharacterBorderCollision(*enemy);
    }

    int collision;
    // check for character collisions with walls
    for (auto& wall : walls) {
        collision = checkCollision(player->getHitBox(), wall->getHitBox());
        if (collision > 0) {
            handleEntityWallCollision(*player, *wall, collision);
        }
        for (auto& enemy : enemies) {
            collision = checkCollision(enemy->getHitBox(), wall->getHitBox());
            if (collision > 0) {
                handleEntityWallCollision(*enemy, *wall, collision);
            }
        }
    }

    // remove recoil from previous actions
    player->removeRecoil();
    for (auto& enemy : enemies) {
        enemy->removeRecoil();
    }

    // move lasers and check for collisions
    for (auto& laser : lasers) {
        laser->move();
        SDL_Rect hitbox = laser->getHitBox();

        if (hitbox.x + hitbox.w < 0 || hitbox.x > levelWidth
            || hitbox.y + hitbox.h < 0 || hitbox.y > levelHeight) {
            laser = nullptr;
        }

        if (laser == nullptr) continue;
        
        // check for laser collision with enemies
        for (auto& enemy : enemies) {
            if (enemy == nullptr) continue;
            collision = checkCollision(laser->getHitBox(),
                enemy->getHitBox());
            if (collision > 0) {
                enemy->changeHP(laser->getDamage() * -1);
                if (enemy->getHP() <= 0) {
                    enemy = nullptr;
                }
                laser = nullptr;
                break;
            }
        }
        
        if (laser == nullptr) continue;
        // check for laser collision with walls
        for (auto& wall : walls) {
            collision = checkCollision(laser->getHitBox(),
                wall->getHitBox());
            if (collision > 0) {
                laser = nullptr;
                break;
            }
        }
    }

    // check for player enemy collision
    if (!player->isInvincible()) {
        for (auto& enemy : enemies) {
            if (enemy == nullptr) continue;
            int collision = checkCollision(player->getHitBox(),
                enemy->getHitBox());
            if (collision > 0) {
                handlePlayerEnemyCollision(*player, collision,
                    enemy->getDamage());
                break;
            }
        }
    }

    // refresh the enemy list
    auto enemyIter = enemies.begin();
    while (enemyIter != enemies.end()) {
        if (*enemyIter == nullptr) {
            enemyIter = enemies.erase(enemyIter);
        } else {
            enemyIter++;
        }
    }

    // refresh laser list
    auto laserIter = lasers.begin();
    while (laserIter != lasers.end()) {
        if (*laserIter == nullptr) {
            laserIter = lasers.erase(laserIter);
        } else {
            laserIter++;
        }
    }
    
    if (player->getHP() <= 0) {
        playerDeath();
    }
}

bool Game::levelCleared() {
    SDL_Rect pHitbox = player->getHitBox();

    if (pHitbox.x >= goal.x && pHitbox.y >= goal.y 
        && pHitbox.x + pHitbox.w <= goal.x + goal.w
        && pHitbox.y + pHitbox.h <= goal.y + goal.h) {
        timer->stop();
        time = 0;
        levelIndex++;
        return true;
    }

    return false;
}

void Game::renderGame(bool dead, bool clear, bool win) {
    view->clearRenderer();
    view->renderTerrain(walls, goal);
    player->notifyObservers();
    for (auto& laser : lasers) {
        laser->notifyObservers();
    }
    for (auto& enemy : enemies) {
        enemy->notifyObservers();
    }
    view->renderStatusText(dead, clear, win);
}

void Game::handlePlayerEnemyCollision(Player& player, int collision,
    int damage) {
    if ((collision & RIGHT) > 0) {
        player.setXRecoil(-10);
    } else if ((collision & LEFT) > 0) {
        player.setXRecoil(10);
    }

    if ((collision & TOP) > 0) {
        player.setYRecoil(10);
    } else if ((collision & BOTTOM) > 0) {
        player.setYRecoil(-10);
    }
    
    player.changeHP(damage * -1);
    player.setInvincibility(true, timer->getTicks());

}

void Game::handleEntityWallCollision(AbstractEntity& entity, Wall& wall,
    int collision) {
    SDL_Rect pHitBox = entity.getHitBox();
    SDL_Rect wHitBox = wall.getHitBox();
    int collisionDepth;

    if ((collision & RIGHT) > 0) {
        collisionDepth = pHitBox.x + pHitBox.w - wHitBox.x;
        if (collisionDepth <= entity.getVelX()) {
            entity.changePosX((collisionDepth + 1) * -1);
        }
    } else if ((collision & LEFT) > 0) {
        collisionDepth = pHitBox.x - wHitBox.x - wHitBox.w;
        if (collisionDepth >= entity.getVelX()) {
            entity.changePosX((collisionDepth - 1) * -1);
        }
    }

    if ((collision & TOP) > 0) {
        collisionDepth = pHitBox.y - wHitBox.y - wHitBox.h;
        if (collisionDepth >= entity.getVelY()) {
            entity.changePosY((collisionDepth - 1) * -1);
        }
    } else if ((collision & BOTTOM) > 0) {
        collisionDepth = pHitBox.y + pHitBox.h - wHitBox.y;
        if (collisionDepth <= entity.getVelY()) {
            entity.changePosY((collisionDepth + 1) * -1);
            entity.setJump(true);
        }
    }
}

int Game::checkCollision(SDL_Rect hitBox1, SDL_Rect hitBox2) {
    int collision = 0;
    
    // sides of hitbox 1
    int left1 = hitBox1.x;
    int right1 = hitBox1.x + hitBox1.w;
    int top1 = hitBox1.y;
    int bottom1 = hitBox1.y + hitBox1.h;

    // sides of hitbox 2
    int left2 = hitBox2.x;
    int right2 = hitBox2.x + hitBox2.w;
    int top2 = hitBox2.y;
    int bottom2 = hitBox2.y + hitBox2.h;

    //TODO: decide one one collision type, not both
    if ((top1 >= top2 && top1 <= bottom2) ||
        (bottom1 >= top2 && bottom1 <= bottom2) || 
        (top1 <= top2 && bottom1 >= bottom2)) {
        int leftDepth = right2 - left1;
        int rightDepth = right1 - left2;
        if (right1 >= left2 && right1 <= right2 && rightDepth < leftDepth) {
            // collision between right1 and left2
            collision = collision | RIGHT;
        } else if (left1 >= left2 && left1 <= right2) {
            // collision between left1 and right2
            collision = collision | LEFT;
        }
    }

    if ((right1 >= left2 && right1 <= right2) ||
        (left1 >= left2 && left1 <= right2) ||
        (left1 <= left2 && right1 >= right2)) {
        if (top1 >= top2 && top1 <= bottom2) {
            // collision between top1 and bottom2
            collision = collision | TOP;
        } else if (bottom1 >= top2 && bottom1 <= bottom2) {
            // collision between bottom1 and top2
            collision = collision | BOTTOM;
        }
    }

    return collision;
}

unique_ptr<MovementStrategy> readMovementStrategy(istringstream& iss) {
    unique_ptr<MovementStrategy> strategy;
    string flag;
    iss >> flag;
    if (flag == "p") {
        int left;
        int right;
        iss >> left;
        iss >> right;
        strategy = make_unique<PatrolStrategy>(left, right);
    } else if (flag == "f") {
        bool flying;
        iss >> flying;
        strategy = make_unique<FollowPlayerStrategy>(flying);
    }

    return strategy;
}

void Game::initLevel() {
    if (levelIndex == NUM_LEVELS) {
        levelIndex = 0;
    }
    walls.clear();
    enemies.clear();
    lasers.clear();
    ifstream file {LEVEL_PATHS[levelIndex]};

    // read in width and height of level
    int dim;
    if (file >> dim) {
        levelWidth = dim;
    }

    if (file >> dim) {
        levelHeight = dim;
    }
    view->setMax(levelWidth, levelHeight);

    // read wall and enemy spawn information
    string s;
    string flag;
    int x, y, w, h;
    while (getline(file, s)) {
        istringstream iss {s};

        iss >> flag;
        iss >> x;
        iss >> y;
        if (flag == "w") { // construct wall
            iss >> w;
            iss >> h;
            walls.push_back(make_unique<Wall>(x, y, w, h));
        } else if (flag == "g") {
            goal = {x, y, 70, 100};
        } else if (flag == "p") {
            player->reset();
            if (player->getHP() <= 0 || levelIndex == 0) {
                player->changeHP(player->getTotalHP() - player->getHP());
            }
            player->changePosX(x);
            player->changePosY(y);
            spawn = {x, y};
        } else if (flag == "mb") {
            unique_ptr<MovementStrategy> strategy = readMovementStrategy(iss);
            enemies.push_back(make_unique<MenacingBlob>(x, y, strategy, 
                view->createMovingObserver(MEN_BLOB_ID, 2)));
        } else if (flag == "z") {
            unique_ptr<MovementStrategy> strategy = readMovementStrategy(iss);
            enemies.push_back(make_unique<Alien>(x, y, strategy,
                view->createMovingObserver(ALIEN_ID, 2)));
        } else if (flag == "b") {
            unique_ptr<MovementStrategy> strategy = readMovementStrategy(iss);
            enemies.push_back(make_unique<Bee>(x, y, strategy,
                view->createMovingObserver(BEE_ID, 2)));
        }
    }
    timer->start();
}

#ifdef DEBUG
void Game::respawnEnemies() {
    enemies.clear();

    ifstream file {LEVEL_PATHS[levelIndex]};
    string s;
    string flag;
    int x, y;
    while (getline(file, s)) {
        istringstream iss {s};

        iss >> flag;
        iss >> x;
        iss >> y;
        if (flag == "mb") {
            unique_ptr<MovementStrategy> strategy = readMovementStrategy(iss);
            enemies.push_back(make_unique<MenacingBlob>(x, y, strategy,
                view->createMovingObserver(MEN_BLOB_ID, 2)));
        } else if (flag == "z") {
            unique_ptr<MovementStrategy> strategy = readMovementStrategy(iss);
            enemies.push_back(make_unique<Alien>(x, y, strategy,
                view->createMovingObserver(ALIEN_ID, 2)));
        } else if (flag == "b") {
            unique_ptr<MovementStrategy> strategy = readMovementStrategy(iss);
            enemies.push_back(make_unique<Bee>(x, y, strategy,
                view->createMovingObserver(BEE_ID, 2)));
        }
    }
}

void Game::killPlayer() {
    player->changeHP(player->getHP() * -1);
}
#endif

void Game::pause() {
    timer->pause();
}

void Game::unpause() {
    timer->unpause();
}

bool Game::isPaused() {
    return timer->isPaused();
}

bool Game::isStarted() {
    return timer->isStarted();
}
