// Game of life
#include "../headers/GameOfLife.h"
// Any live cell with fewer than two live neighbors dies, as if by under population.
// Any live cell with two or three live neighbors lives on to the next generation.
// Any live cell with more than three live neighbors dies, as if by overpopulation.
// Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
#include <iostream>

void GameOfLife::init()
{
    nextNumber.seed(SDL_GetTicks());
    gridSize = {64, 64};
    cells = new Cell[gridSize.x * gridSize.y];
    cellSize = 8;
    int distX=0;
    int distY = 0;
    for (int i = 0; i < (gridSize.x * gridSize.y); ++i)
    {        
        if(randomNumbers(nextNumber) >= 0.7)
        {
            cells[i].isAlive = true;
            cells[i].wasAlive = true;
            distX++;            
        }
        else
        { 
            cells[i].isAlive = false;
            cells[i].wasAlive = false;
            distY++;
        }
        std::cout << "x: " << distX << " y: " << distY << std::endl;
    }
}

void GameOfLife::setLife()
{
    for (int i = 0; i < gridSize.x * gridSize.y; ++i)
    {
        cells[i].wasAlive = cells[i].isAlive;
        int liveNeighbours = 0;
        int xPos = i % gridSize.x;
        int yPos = i / gridSize.x;

        if(yPos > 0)
        {
            if(xPos > 0)
                if(cells[i - gridSize.x - 1].wasAlive) ++liveNeighbours;
            if(cells[i - gridSize.x].wasAlive) ++liveNeighbours;
            if(xPos < (gridSize.x - 1)) 
                if(cells[i - gridSize.x + 1].wasAlive) ++liveNeighbours;        
        }

        if(xPos > 0)
            if(cells[i-1].wasAlive) ++liveNeighbours;
        if(xPos < (gridSize.x -1)) 
            if(cells[i+1].isAlive) ++liveNeighbours;

        if(yPos < (gridSize.y - 1))
        {
            if(xPos > 0)
                if(cells[i + gridSize.x - 1].isAlive) ++liveNeighbours;
            if(cells[i + gridSize.x].isAlive) ++liveNeighbours;
            if(xPos < (gridSize.x - 1)) 
                if(cells[i + gridSize.x + 1].isAlive) ++liveNeighbours;        
        }

        if(liveNeighbours < 2 || liveNeighbours > 3) cells[i].isAlive = false;
        else if(cells[i].wasAlive == false) {
            if(liveNeighbours == 3) cells[i].isAlive = true;
        }
        else cells[i].isAlive = true;
    }
}

void GameOfLife::render(SDL_Renderer* renderer) 
{

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 128, 0, 0);
    for (int i = 0; i < gridSize.x * gridSize.y; ++i)
    {
        if(cells[i].isAlive) 
        {
            SDL_Rect target = { (i % gridSize.x) * cellSize, 
                                (i / gridSize.x) * cellSize, 
                                cellSize, 
                                cellSize };
            SDL_RenderFillRect(renderer, &target);
        }
    }
}

