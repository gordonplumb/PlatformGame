#ifndef _VIEW_
#define _VIEW_

#include <string>
#include <map>
#include <vector>
#include <sstream>

class SDL_Renderer;
class SDL_Window;
class SDL_Rect;
class SDL_Point;
class SDL_Color;
typedef struct _TTF_Font TTF_Font;
class TextureWrapper;
class Observer;
class Wall;

class View {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Color* fontColour;
    std::map<int, TextureWrapper*> textures;
    std::vector<Observer*> observers;
    SDL_Rect* camera;
    SDL_Point* max;
    std::stringstream timeText;

    TextureWrapper* loadTexture(std::string path, int height = 0, int width = 0);
    TextureWrapper* loadTextureFromText(std::string text);
    void loadTextures();

    public:
    View();
    ~View();
    bool init();
    void renderTerrain(std::vector<Wall*> walls, SDL_Rect goal);
    void renderStatusText(bool gameOver, bool levelClear, bool win);
    void clearRenderer();
    Observer* createMovingObserver(int id, int maxWalkFrame, int xOffset = 0,
                                   int yOffset = 0);
    Observer* createPlayerStatusObserver();
    void removeObserver(Observer* observer);

    void updateCamera(SDL_Point* point);
    void setMax(SDL_Point* max);

    void updateTime(uint32_t time);

    SDL_Renderer* getRenderer();
    SDL_Rect* getCamera();
};

#endif