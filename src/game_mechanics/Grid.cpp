#include "../headers/Grid.h"
#include "../headers/Constants.h"
#include <iostream>

Grid::Grid() 
{
    cellSize = { SQUARE - OFFSET*2, SQUARE - OFFSET*2 };
}

void Grid::render(SDL_Renderer* renderer, Node* nodes)
{
    SDL_Rect target = { 0, 0, cellSize.x, cellSize.y };
    for( int x = 0; x < WIDTH; x++ )
    {   
        target.x = (x * SQUARE) + OFFSET;
        for( int y = 0; y < HEIGHT; y++)
        {
            target.y = (y * SQUARE) + OFFSET;
            // std::cout << "current x: " << x << " y: " << y << std::endl;
            if(nodes[x + y * WIDTH].hasObstacle) SDL_SetRenderDrawColor(renderer, 128, 128, 128, 0);
            else SDL_SetRenderDrawColor(renderer, 255, 128, 0, 0);
            SDL_RenderFillRect(renderer, &target);
        }
    }
}
