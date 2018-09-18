#include "../headers/Viewport.h"
#include <iostream>


Viewport::Viewport()
{
    // for demo purposes
    texture = nullptr;
    frame = nullptr;
    // outline = { 800, 0, 224, 768 };
    // texture = SDL_CreateTexture(Screen::getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, outline.w, outline.h);
    // frame = SDL_CreateTexture(Screen::getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, outline.w, outline.h);
    // setFrame();
    // std::cout << __func__ << std::endl;
    // ViewportButton button;
    // items.push_back(button);
}

void Viewport::setTexture(){};

void Viewport::setOutline(SDL_Rect newOutline)
{ 
    outline = newOutline;
    if(texture != nullptr) SDL_DestroyTexture(texture);
    if(frame != nullptr) SDL_DestroyTexture(frame);
    texture = SDL_CreateTexture(Screen::getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, outline.w, outline.h);
    frame = SDL_CreateTexture(Screen::getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, outline.w, outline.h);
    setFrame();
}

void Viewport::setFrame()
{
    float magnifier = 2;
    int cornerWidth = 8;
    int cornerHeight = 8;
    int frameThickness = 6;
    int cornerLocationOffset = 11;
    int frameLocationOffset = 13 ;
    int frameLength = 1;

    int targetWidth = cornerWidth* magnifier;
    int targetHeight = cornerHeight* magnifier;
    int targetThickness = frameThickness * magnifier;

    SDL_Renderer* renderer = Screen::getRenderer();
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, 200, 100, 0, 0);
    SDL_RenderClear(renderer);

    SDL_Texture* textureMap = Factory::instance() -> image("resources/wood.png");
    
    SDL_Rect cornerMapIndex = { 0, 
                                0, 
                                cornerWidth, 
                                cornerHeight }; // hard coded for now

    SDL_Rect cornerTarget = {   0, 
                                0, 
                                targetWidth, 
                                targetHeight };
    SDL_RenderCopy(renderer, textureMap, &cornerMapIndex, &cornerTarget); // top left
    
    cornerMapIndex.x = cornerLocationOffset;
    cornerTarget.x = outline.w - targetWidth, 
    SDL_RenderCopy(renderer, textureMap, &cornerMapIndex, &cornerTarget); // top right
   
    cornerMapIndex.y = cornerLocationOffset;
    cornerTarget.y = outline.h - targetHeight;
    SDL_RenderCopy(renderer, textureMap, &cornerMapIndex, &cornerTarget); // bottom right
   
    cornerMapIndex.x = 0;
    cornerTarget.x = 0;
    SDL_RenderCopy(renderer, textureMap, &cornerMapIndex, &cornerTarget); // bottom left

    // render vertical frame
    SDL_Rect mapIndex = {   cornerWidth, 
                            0, 
                            frameLength, 
                            frameThickness };

    SDL_Rect target = {     targetWidth, 
                            0, 
                            outline.w - targetWidth * 2, 
                            targetThickness };
    SDL_RenderCopy(renderer, textureMap, &mapIndex, &target); // top horizontal

    mapIndex.y = frameLocationOffset;
    target.y = outline.h - targetThickness;
    SDL_RenderCopy(renderer, textureMap, &mapIndex, &target); // bottom horizontal

    mapIndex.x = 0;
    mapIndex.y = cornerHeight, 
    mapIndex.w = frameThickness;
    mapIndex.h = frameLength;
    target = {      0, 
                    targetHeight, 
                    targetThickness, 
                    outline.h - targetHeight * 2 };

    SDL_RenderCopy(renderer, textureMap, &mapIndex, &target); // left vertical

    mapIndex = {    frameLocationOffset, 
                    cornerHeight, 
                    frameThickness, 
                    frameLength };

    target = {      outline.w - targetThickness, 
                    targetHeight, 
                    targetThickness, 
                    outline.h - targetHeight * 2 };
    SDL_RenderCopy(renderer, textureMap, &mapIndex, &target); // right vertical

    SDL_SetRenderTarget(Screen::getRenderer(), nullptr);

}

void Viewport::update()
{
};


void Viewport::render(SDL_Renderer* renderer)
{
    SDL_RenderSetViewport(renderer, &outline);
    // SDL_RenderCopy(renderer, frame, nullptr, nullptr);


    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    for(auto const& item : items)
    {
        if(item.index.w == 0 ) SDL_RenderCopy(renderer, item.texture, nullptr, &item.position);
        else SDL_RenderCopy(renderer, item.texture, &item.index, &item.position);
    }
    SDL_RenderSetViewport(renderer, nullptr);
}

void Viewport::click(SDL_Point& mouse)
{
    std::cout << "outlines x: " << outline.x << " y: " << outline.y << std::endl;
    if(mouse.x > outline.x 
        && mouse.x < outline.w + outline.x
        && mouse.y > outline.y
        && mouse.y < outline.y + outline.h)
    {
        // Viewport has been clicked
        std::cout << "Clicked in viewport" << std::endl;

        // Normalize
        int mouseX = mouse.x - outline.x;
        int mouseY = mouse.y - outline.y;
        std::cout << mouseX << " x " << mouseY << std::endl;
        std::cout << "outlines x: " << outline.x << " y: " << outline.y << std::endl;
        for(auto& item : items)
        {
            if(mouseX > item.position.x 
                && mouseX < item.position.x + item.position.w
                && mouseY > item.position.y
                && mouseY < item.position.y + item.position.h)
            {
                std::cout << "CLICKED" << std::endl;
                break;
            }
        }
    }
}

ViewportButton* Viewport::addButton(SDL_Renderer* renderer) 
{
    // check if too big
    ViewportButton* pButton = new ViewportButton();
    items.push_back(*pButton);
    return pButton;


    // SDL_Rect target = { 50, 50, 128, 64 };
    // SDL_Texture* texture = Factory::instance() -> image("resources/button.png");
    // SDL_SetRenderTarget(renderer, this -> texture);
    // SDL_RenderCopy(renderer, texture, NULL, &target);
    // SDL_DestroyTexture(texture);
    // SDL_SetRenderTarget(renderer, NULL);
}

ViewportButton* Viewport::addButton(SDL_Renderer* renderer, 
                                    std::string title,
                                    SDL_Rect index, 
                                    SDL_Rect position) 
{
    // check if too big
    ViewportButton* pButton = new ViewportButton(title, index, position);
    items.push_back(*pButton);
    return pButton;


    // SDL_Rect target = { 50, 50, 128, 64 };
    // SDL_Texture* texture = Factory::instance() -> image("resources/button.png");
    // SDL_SetRenderTarget(renderer, this -> texture);
    // SDL_RenderCopy(renderer, texture, NULL, &target);
    // SDL_DestroyTexture(texture);
    // SDL_SetRenderTarget(renderer, NULL);
}