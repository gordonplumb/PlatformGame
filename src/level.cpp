#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <level.h>
#include <wall.h>
#include <menacingblob.h>

using namespace std;

Level::Level(string filePath): mFilePath {filePath} {}

Level::~Level() {}

bool Level::init() {
    ifstream file {mFilePath};

    // read in width and height of level
    int dim;
    if (file >> dim) {
        mWidth = dim;
    } else {
        cerr << "failed to read width" << endl;
        return false;
    }

    if (file >> dim) {
        mHeight = dim;
    } else {
        cerr << "failed to read height" << endl;
        return false;
    }

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
            mWalls.emplace_back(new Wall(x, y, w, h));
        } else if (flag == "mb") {
            iss >> x;
            iss >> y;
            mEnemies.emplace_back(new MenacingBlob(x, y));
        }
    }

    return true;
}

void Level::render() {
    for (Wall* wall : mWalls) {
        wall->render();
    }

    for (AbstractEnemy* enemy : mEnemies) {
        enemy->render();
    }
}

vector<Wall*> Level::getWalls() {
    return mWalls;
}

vector<AbstractEnemy*> Level::getEnemies() {
    return mEnemies;
}

vector<Laser*> Level::getLasers() {
    return mLasers;
}

void Level::addLaser(Laser* laser) {
    mLasers.emplace_back(laser);
}

void Level::updateLasers(vector<Laser*> lasers) {
    mLasers = lasers;
}
