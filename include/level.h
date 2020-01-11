#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <vector>
#include <string>

class Wall;
class AbstractEnemy;
class Laser;

class Level {
    std::vector<Wall*> mWalls;
    std::vector<AbstractEnemy*> mEnemies;
    std::vector<Laser*> mLasers;
    std::string mFilePath;
    int mWidth;
    int mHeight;

    public:
    Level(std::string filePath);
    ~Level();

    bool init();
    void render(int camX, int camY);
    std::vector<Wall*> getWalls();
    std::vector<AbstractEnemy*> getEnemies();
    std::vector<Laser*> getLasers();
    void addLaser(Laser* laser);
    void updateLasers(std::vector<Laser*> lasers);

    int getWidth();
    int getHeight();
};

#endif