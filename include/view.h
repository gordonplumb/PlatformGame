#ifndef _VIEW_
#define _VIEW_

#include <string>
#include <map>
#include <vector>

class SDL_Renderer;
class SDL_Window;
class SDL_Rect;
class SDL_Point;
class TextureWrapper;
class Observer;
class Wall;

class View {
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::map<int, TextureWrapper*> textures;
    std::vector<Observer*> observers;
    SDL_Rect* camera;
    SDL_Point* max;

    TextureWrapper* loadTexture(std::string path, int height = 0, int width = 0);
    void loadTextures();

    public:
    View();
    ~View();
    bool init();
    void render(std::vector<Wall*> walls);
    void clearRenderer();
    Observer* createObserver(int id, int maxWalkFrame, int xOffset = 0,
                             int yOffset = 0);
    void removeObserver(Observer* observer);

    void updateCamera(SDL_Point* point);
    void setMax(SDL_Point* max);

    SDL_Renderer* getRenderer();
    SDL_Rect* getCamera();
};

#endif