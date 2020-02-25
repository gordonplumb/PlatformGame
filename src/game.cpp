#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <game.h>
#include <view.h>
#include <timer.h>
#include <gameconstants.h>
#include <wall.h>
#include <player.h>
#include <menacingblob.h>
#include <laser.h>
using namespace std;

const int RIGHT = 1;
const int LEFT = 2;
const int TOP = 4;
const int BOTTOM = 8;

Game::Game(View* view) {
    this->view = view;
    timer = new Timer();
    mPlayer = new Player(view->createMovingObserver(PLAYER_ID, 2, 5, 10));
    mPlayer->addObserver(view->createPlayerStatusObserver());
}

void Game::playerJump() {
    if (mPlayer->canJump() && !mPlayer->isCrouching()) {
        mPlayer->changeVelY(-15);
        mPlayer->setJump(false);
    }
}

void Game::playerLookUp(bool isLookingUp) {
    mPlayer->setLookingUp(isLookingUp);
}

void Game::playerCrouch(bool isCrouching, bool left, bool right) {
    if (isCrouching) {
        if (left) {
            mPlayer->changeVelX(Player::PLAYER_MAX_SPEED);
        }
        if (right) {
            mPlayer->changeVelX(Player::PLAYER_MAX_SPEED * -1);
        }
    } else {
        if (left) {
            mPlayer->changeVelX(Player::PLAYER_MAX_SPEED * -1);
        }
        if (right) {
            mPlayer->changeVelX(Player::PLAYER_MAX_SPEED);
        }
    }
    mPlayer->setCrouch(isCrouching);
}

void Game::playerMove(bool stop, bool forward) {
    int multiplier = forward ? 1 : -1;
    if (stop) {
        multiplier *= -1;
    }
    if (!mPlayer->isCrouching()) {
        mPlayer->changeVelX(Player::PLAYER_MAX_SPEED * multiplier);
    }
}

void Game::playerShoot() {
    Laser* laser;
    laser = mPlayer->fireLaser();
    laser->addObserver(view->createMovingObserver(LASER_ID, 0));
    lasers.emplace_back(laser);
}

void Game::playerDeath() {
    timer->stop();
}

void Game::resetPlayerActions(bool left, bool right, bool up, bool down) {
    // resetting all actions that result from a held key 
    if (left) {
        if (!mPlayer->isCrouching()) {
            mPlayer->changeVelX(Player::PLAYER_MAX_SPEED);
        }
    }
    if (right) {
        if (!mPlayer->isCrouching()) {
            mPlayer->changeVelX(Player::PLAYER_MAX_SPEED * -1);
        }
    }
    if (up) {
        mPlayer->setLookingUp(false);
    }
    if (down) {
        mPlayer->setCrouch(false);
    }
}

void Game::update() {
    if (!(isPaused() || !isStarted())) {
        moveEntities();
        renderGame();
    }
}

void Game::handleCharacterBorderCollision(AbstractEntity* entity) {
    SDL_Rect hitbox = entity->getHitBox();
    if (hitbox.x < 0 || hitbox.x + hitbox.w > levelWidth) {
        entity->changePosX(entity->getVelX() * -1);
    }

    if (hitbox.y < 0 || hitbox.y + hitbox.h > levelHeight) {
        entity->changePosY(entity->getVelY() * -1);
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
    mPlayer->move(elapsed);
    handleCharacterBorderCollision(mPlayer);
    for (AbstractEnemy *enemy : enemies) {
        enemy->move(elapsed);
        handleCharacterBorderCollision(enemy);
    }

    int collision;
    // check for character collisions with walls
    for (Wall *wall : walls) {
        collision = checkCollision(mPlayer->getHitBox(), wall->getHitBox());
        if (collision > 0) {
            handleEntityWallCollision(mPlayer, wall, collision);
        }
        for (AbstractEnemy *enemy : enemies) {
            collision = checkCollision(enemy->getHitBox(), wall->getHitBox());
            if (collision > 0) {
                handleEntityWallCollision(enemy, wall, collision);
            }
        }
    }

    // move lasers and check for collisions
    for (int i = 0; i < lasers.size(); i++) {
        lasers[i]->move(elapsed);
        SDL_Rect hitbox = lasers[i]->getHitBox();

        if (hitbox.x + hitbox.w < 0 || hitbox.x > levelWidth
            || hitbox.y + hitbox.h < 0 || hitbox.y > levelHeight) {
            Laser* temp = lasers[i];
            lasers[i] = nullptr;
            delete temp;
        }

        if (lasers[i] == nullptr) continue;
        
        // check for laser collision with enemies
        for (int j = 0; j < enemies.size(); j++) {
            if (enemies[j] == nullptr) continue;
            collision = checkCollision(lasers[i]->getHitBox(),
                enemies[j]->getHitBox());
            if (collision > 0) {
                enemies[j]->changeHP(lasers[i]->getDamage() * -1);
                if (enemies[j]->getHP() <= 0) {
                    AbstractEnemy* temp = enemies[j];
                    enemies[j] = nullptr;
                    delete temp;
                }
                Laser* temp = lasers[i];
                lasers[i] = nullptr;
                delete temp;
                break;
            }
        }
        
        if (lasers[i] == nullptr) continue;
        // check for laser collision with walls
        for (Wall *wall : walls) {
            collision = checkCollision(lasers[i]->getHitBox(), wall->getHitBox());
            if (collision > 0) {
                Laser* temp = lasers[i];
                lasers[i] = nullptr;
                delete temp;
                break;
            }
        }
    }

    // check for player enemy collision
    if (!mPlayer->isInvincible()) {
        for (AbstractEnemy *enemy : enemies) {
            if (enemy == nullptr) continue;
            int collision = checkCollision(mPlayer->getHitBox(),
                enemy->getHitBox());
            if (collision > 0) {
                handlePlayerEnemyCollision(mPlayer, collision,
                    enemy->getDamage());
                break;
            }
        }
    }

    // refresh the enemy list
    vector<AbstractEnemy*> newEnemies;
    for (AbstractEnemy * enemy : enemies) {
        if (enemy != nullptr) {
            newEnemies.push_back(enemy);
        }
    }
    enemies = newEnemies;

    // refresh laser list
    vector<Laser*> newLasers;
    for (Laser* laser : lasers) {
        if (laser != nullptr) {
            newLasers.push_back(laser);
        }
    }
    lasers = newLasers;

    if (collision > 0 && mPlayer->getHP() > 0) {
        // check if the player was pushed into a wall by enemy
        for (Wall *wall : walls) {
            collision = checkCollision(mPlayer->getHitBox(), wall->getHitBox());
            if (collision > 0) {
                handleEntityWallCollision(mPlayer, wall, collision);
            }
        }
    } else if (mPlayer->getHP() <= 0) {
        playerDeath();
    }
}

void Game::renderGame() {
    view->clearRenderer();
    mPlayer->notifyObservers();
    for (Laser* laser : lasers) {
        laser->notifyObservers();
    }
    for (AbstractEnemy* enemy : enemies) {
        enemy->notifyObservers();
    }
    view->render(walls, mPlayer->getHP() <= 0);
}

void Game::renderDeathScreen() {
}

void Game::handlePlayerEnemyCollision(Player* player, int collision, int damage) {
    if ((collision & RIGHT) > 0) {
        player->setXRecoil(-10);
    } else if ((collision & LEFT) > 0) {
        player->setXRecoil(10);
    }

    if ((collision & TOP) > 0) {
        player->setYRecoil(10);
    } else if ((collision & BOTTOM) > 0) {
        player->setYRecoil(-10);
    }
    
    player->changeHP(damage * -1);
    player->setInvincibility(true, timer->getTicks());

}

void Game::handleEntityWallCollision(AbstractEntity* entity, Wall* wall, int collision) {
    SDL_Rect pHitBox = entity->getHitBox();
    SDL_Rect wHitBox = wall->getHitBox();
    int collisionDepth;

    if ((collision & RIGHT) > 0) {
        collisionDepth = pHitBox.x + pHitBox.w - wHitBox.x;
        if (collisionDepth < entity->getVelX()) {
            entity->changePosX(entity->getVelX() * -1);
        }
    } else if ((collision & LEFT) > 0) {
        collisionDepth = pHitBox.x - wHitBox.x - wHitBox.w;
        if (collisionDepth > entity->getVelX()) {
            entity->changePosX(entity->getVelX() * -1);
        }
    }

    if ((collision & TOP) > 0) {
        collisionDepth = pHitBox.y - wHitBox.y - wHitBox.h;
        if (collisionDepth > entity->getVelY()) {
            entity->changePosY(entity->getVelY() * -1);
        }
    } else if ((collision & BOTTOM) > 0) {
        collisionDepth = pHitBox.y + pHitBox.h - wHitBox.y;
        if (collisionDepth < entity->getVelY()) {
            entity->changePosY(entity->getVelY() * -1);
            entity->setJump(true);
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
        }
        if (bottom1 >= top2 && bottom1 <= bottom2) {
            // collision between bottom1 and top2
            collision = collision | BOTTOM;
        }
    }

    return collision;
}

void Game::initLevel(string path) {
    levelPath = path;
    ifstream file {levelPath};

    // read in width and height of level
    int dim;
    if (file >> dim) {
        levelWidth = dim;
    }

    if (file >> dim) {
        levelHeight = dim;
    }
    view->setMax(new SDL_Point {levelWidth, levelHeight});

    // read wall and enemy spawn information
    string s;
    string flag;
    int x, y, w, h;
    while (getline(file, s)) {
        istringstream iss {s};

        iss >> flag;
        if (flag == "w") { // construct wall
            iss >> x;
            iss >> y;
            iss >> w;
            iss >> h;
            walls.emplace_back(new Wall(x, y, w, h));
        } else if (flag == "mb") {
            iss >> x;
            iss >> y;
            enemies.emplace_back(new MenacingBlob(x, y, view->createMovingObserver(MEN_BLOB_ID, 2)));
        }
    }

    timer->start();
}

#ifdef DEBUG
void Game::respawnEnemies() {
    enemies.clear();

    ifstream file {levelPath};
    string s;
    string flag;
    int x, y;
    while (getline(file, s)) {
        istringstream iss {s};

        iss >> flag;
        if (flag == "mb") {
            iss >> x;
            iss >> y;
            enemies.emplace_back(new MenacingBlob(x, y, view->createMovingObserver(MEN_BLOB_ID, 2)));
        }
    }
}

void Game::killPlayer() {
    mPlayer->changeHP(mPlayer->getHP() * -1);
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
