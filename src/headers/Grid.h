#ifndef GRID_H_
#define GRID_H_ 

#include <SDL2/SDL.h>
#include "Pathfinder.h"

class Grid
{
public:
    Grid();
    void render(SDL_Renderer* renderer, Node* nodes);

protected:

private:
    SDL_Point cellSize;
};

#endif
