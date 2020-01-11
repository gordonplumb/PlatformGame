#include <game.h>
#include <gameconstants.h>
#include <level.h>
#include <wall.h>
#include <player.h>
#include <menacingblob.h>
#include <laser.h>
#include <iostream>
using namespace std;

const int RIGHT = 1;
const int LEFT = 2;
const int TOP = 4;
const int BOTTOM = 8;

bool Game::init() {
    mPlayer = new Player();

    return true;
}

void Game::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        switch(event.key.keysym.sym) {
            case SDLK_UP:
            if (mPlayer->canJump()) {
                mPlayer->changeVelY(-15);
                mPlayer->setJump(false);
            }
            break;

            case SDLK_DOWN:
            break;

            case SDLK_LEFT:
            mPlayer->changeVelX(Player::PLAYER_MAX_SPEED * -1);
            break;

            case SDLK_RIGHT:
            mPlayer->changeVelX(Player::PLAYER_MAX_SPEED);
            break;

            case SDLK_z:
            mLevel->addLaser(mPlayer->fireLaser());
            break;

            default:
            break;
        }
    } else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
            mPlayer->changeVelY(Player::PLAYER_MAX_SPEED);
            break;

            case SDLK_DOWN:
            break;

            case SDLK_LEFT:
            mPlayer->changeVelX(Player::PLAYER_MAX_SPEED);
            break;

            case SDLK_RIGHT:
            mPlayer->changeVelX(Player::PLAYER_MAX_SPEED * -1);
            break;
        }
    }
}

void Game::moveEntities() {
    vector<AbstractEnemy*> enemies = mLevel->getEnemies();
    vector<Wall*> walls = mLevel->getWalls();
    vector<Laser*> lasers = mLevel->getLasers();

    vector<int> removeList;
    for (int i = 0; i < lasers.size(); i++) {
        Laser* laser = lasers.at(i);
        laser->move(0, mLevel->getHeight(), mLevel->getWidth(), 0);
        for (Wall* wall : walls) {
            int collision = checkCollision(laser->getHitBox(), wall->getHitBox());
            if (collision > 0) {
                removeList.push_back(i);
            }
        }
    }
    int removed = 0;
    for (int i : removeList) {
        lasers.erase(lasers.begin() + i - removed);
        removed++;
    }

    // move the player, make sure they're not in a wall
    mPlayer->move(0, mLevel->getHeight(), mLevel->getWidth(), 0);
    for (Wall* wall : walls) {
        int collision = checkCollision(mPlayer->getHitBox(), wall->getHitBox());
        if (collision > 0) {
            handleEntityWallCollision(mPlayer, wall, collision);
        }
    }

    // for each enemy: move the enemy
    //                 ensure they're not in any walls
    //                 check for player-enemy collision
    for (AbstractEnemy* enemy : enemies) {
        enemy->move(0, mLevel->getHeight(), mLevel->getWidth(), 0);
        for (Wall* wall : walls) {
            int collision = checkCollision(enemy->getHitBox(), wall->getHitBox());
            if (collision > 0) {
                handleEntityWallCollision(enemy, wall, collision);
            }
        }
        int collision = checkCollision(mPlayer->getHitBox(), enemy->getHitBox());
        if (collision > 0) {
            handlePlayerEnemyCollision(mPlayer, collision);
        }
    }
    mLevel->updateLasers(lasers);
}

void Game::handlePlayerEnemyCollision(Player* player, int collision) {
    // change this to set vel instead
    if ((collision & RIGHT) > 0) {
        player->changePosX(-5);
    } else if ((collision & LEFT) > 0) {
        player->changePosX(5);
    }

    if ((collision & TOP) > 0) {
        player->changePosY(5);
    } else if ((collision & BOTTOM) > 0) {
        player->changePosY(-5);
    }
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

void Game::render(int camX, int camY) {
    vector<AbstractEnemy*> enemies = mLevel->getEnemies();
    vector<Wall*> walls = mLevel->getWalls();
    vector<Laser*> lasers = mLevel->getLasers();
    mPlayer->render(camX, camY);
    for (AbstractEnemy* enemy : enemies) {
        enemy->render(camX, camY);
    }
    for (Wall* wall : walls) {
        wall->render(camX, camY);
    }
    for (Laser* laser : lasers) {
        laser->render(camX, camY);
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

void Game::setLevel(Level* level) {
    mLevel = level;
}

SDL_Point Game::getFocus() {
    return SDL_Point {mPlayer->getHitBox().x + (mPlayer->PLAYER_WIDTH - SCREEN_WIDTH) / 2,
                      mPlayer->getHitBox().y + (mPlayer->PLAYER_HEIGHT - SCREEN_HEIGHT) / 2};
}

SDL_Point Game::getMax() {
    return SDL_Point {mLevel->getWidth(), mLevel->getHeight()};
}
