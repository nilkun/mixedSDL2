#include "../../headers/ViewportItem.h"
#include <string>
#include <iostream>
#include "../../engine/headers/Factory.h"

// button has size color and text and onClick 
ViewportButton::ViewportButton()
{
    // check if too big
    position = { 50, 200, 128, 64 };
    // texture = Factory::instance() -> image("resources/button.png");
    title = "TEXT";
    texture = Factory::instance() -> text(title);
    index = {0,0,0,0};

    // a button has a location, a text or icon, and can be clicked
    // void onClick() { std::cout << "CLICKED A BUTTON!!!"; }
    // void renderer(SDL_Renderer* renderer);\?*std::string title:

}
ViewportButton::ViewportButton(std::string title, 
                                SDL_Rect index,
                                SDL_Rect position)
                                : title(title),
                                ViewportItem(index, position)
{
    texture = Factory::instance() -> text(title);
    std::cout << "CREATED" << title << std::endl;

}


void ViewportButton::createTexture()
{
    texture = Factory::instance() -> text(title);
    position = { 50, 200, 128, 64 };
    index = {0, 0, 0, 0};
}

void ViewportButton::click() { std::cout << "CLICKED A BUTTON!!!"; }