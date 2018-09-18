#ifndef VIEWPORTITEM_H_
#define VIEWPORTITEM_H_
#include <SDL2/SDL.h>
#include <string>

struct ViewportItem 
{
public:

    SDL_Rect index; // So it can have a nullptr, used for rendering
    SDL_Rect position;
    SDL_Texture* texture;

    ViewportItem(){};
    ViewportItem(SDL_Rect index, SDL_Rect position):index(index), position(position){};
  
    // virtual void render();
    // virtual void click()=0;
   
};

struct ViewportButton : public ViewportItem
{
    std::string title;
    ViewportButton();
    ViewportButton(std::string title, 
        SDL_Rect index,
        SDL_Rect position);
    void click();
    // void render();
    // a button has a location, a text or icon, and can be clicked
    // void onClick() { std::cout << "CLICKED A BUTTON!!!"; }
    void createTexture();
    

};

#endif
