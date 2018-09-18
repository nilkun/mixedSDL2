#ifndef VIEWPORT_H_
#define VIEWPORT_H_
#include <SDL2/SDL.h>
#include "../engine/headers/ScreenManager.h"
#include "../engine/headers/Factory.h"
#include "../headers/ViewportItem.h"
#include <vector>

class Viewport
{
public:
    Viewport();
    void render(SDL_Renderer* renderer);
    void setFrame();
    void setOutline(SDL_Rect newOutline);

    void setTexture();
    void update();
    void click(SDL_Point& mouse);
    ViewportButton* addButton(SDL_Renderer* renderer);
    ViewportButton* addButton(SDL_Renderer* renderer, 
                                    std::string title,
                                    SDL_Rect index, 
                                    SDL_Rect position);

    std::vector<ViewportItem> items; // placeholder for items

protected:
private:
    SDL_Rect outline;   // Location of viewport on screen
    SDL_Texture* texture;
    SDL_Texture* frame;     // make a FramedViewport class
};

#endif

