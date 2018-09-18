#ifndef GAMEOFLIFE_H_
#define GAMEOFLIFE_H_

#include <SDL2/SDL.h>
#include <vector>
#include <random>


struct Cell
{
public:
    bool wasAlive;
    bool isAlive;
};

class GameOfLife
{
public:
    Cell *cells;
    SDL_Point gridSize;
    void init();
    void setLife();
    void render(SDL_Renderer* renderer);
    std::mt19937 nextNumber;
    std::uniform_real_distribution<double> randomNumbers{0.0,1.0};
    int cellSize;
};

#endif