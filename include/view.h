#ifndef VIEW_H
#define VIEW_H

#include <string>
#include <map>
#include <memory>
#include <vector>
#include <sstream>
#include <SDL2/SDL.h>

typedef struct _TTF_Font TTF_Font;
class TextureWrapper;
class Observer;
class Wall;

class View: public std::enable_shared_from_this<View> {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Color fontColour;
    std::map<int, std::shared_ptr<TextureWrapper>> textures;
    SDL_Rect camera;
    SDL_Point max;
    std::stringstream timeText;

    std::shared_ptr<TextureWrapper> loadTexture(std::string path,
        int height = 0, int width = 0);
    std::shared_ptr<TextureWrapper> loadTextureFromText(std::string text);
    void loadTextures();

    std::shared_ptr<View> getSharedPtr();

    public:
    View();
    ~View();
    bool init();

    // rendering functions
    void renderTerrain(std::vector<std::unique_ptr<Wall>>& walls,
        SDL_Rect goal);
    void renderStatusText(bool gameOver, bool levelClear, bool win);
    void clearRenderer();

    // manage observers
    std::unique_ptr<Observer> createMovingObserver(int id, int maxWalkFrame,
        int xOffset = 0, int yOffset = 0);
    std::unique_ptr<Observer> createPlayerStatusObserver();

    
    void updateCamera(SDL_Point point);
    void setMax(int x, int y); // max point to render

    void updateTime(uint32_t time);

    SDL_Renderer* getRenderer();
    SDL_Rect getCamera();
};

#endif