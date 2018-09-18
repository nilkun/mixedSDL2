#include <SDL2/SDL.h>

// Engine files
#include "engine/headers/ScreenManager.h"
#include "engine/headers/Factory.h"

// Game files
#include "headers/EventHandler.h"

#include "headers/MovingEntity.h"
#include "headers/Vector2D.h"
#include "headers/Vehicle.h"
#include "engine/headers/GameEntity.h"
#include "headers/GameOfLife.h"

// STL
#include <vector>
#include <string>
#include <iostream>
#include "headers/Perlin.h"
#include "headers/Constants.h"
#include "headers/Grid.h"
#include "headers/Pathfinder.h"
#include "headers/Viewport.h"

int main()
{
  bool reRender = false;
  // Create objects and get instances
  EventHandler events;
  Screen *screen = Screen::instance();
  Factory *factory = Factory::instance();

  screen -> init("Steering", SCREEN_WIDTH, SCREEN_HEIGHT);
  factory -> init();
  SDL_Renderer* renderer = screen -> getRenderer();

//VEHICLE
  // Vehicle vehicle;
  // SDL_Texture* texture = factory -> image("resources/explorer.png");
  // vehicle.m_vPos.x = 10;
  // vehicle.m_vPos.y = 10;
  // vehicle.target.x = 500;
  // vehicle.target.y = 500;

  double current = SDL_GetTicks();
  double previous = SDL_GetTicks();
  double delta = 0;
  // SDL_Rect location = { vehicle.m_vPos.x, vehicle.m_vPos.y, 64, 64 };
  // /* This is the game loop. It should be short and concise. */




//PERLIN
  // Perlin perlin;
  // perlin.render1d(screen -> getRenderer());


//PATHFINDER
  // Grid grid;
   Pathfinder pathfinder;
  // SDL_Point cellSize = { SQUARE - OFFSET*2, SQUARE - OFFSET*2 };
  // SDL_Rect target = { 0, 0, cellSize.x, cellSize.y };

Viewport sideViewport;
Viewport mainViewport;

std::vector<Viewport> vps;
{
  SDL_Rect outline = { 800, 0, 224, 768 };
  sideViewport.setOutline(outline);
  outline = { 0, 0, 800, 768 };
  
  mainViewport.setOutline(outline);
  mainViewport.addButton(renderer);

  SDL_Rect fillAll = { 0, 0, 0, 0 };
  outline = { 20, 20, 10 * 12, 18 };
  sideViewport.addButton(renderer, "Perlin noise", fillAll, outline );


  outline = { 20, 40, 10 * 12, 18 };
  sideViewport.addButton(renderer, "Game of Life", fillAll, outline );


  outline = { 20, 60, 10 * 14, 18 };
  sideViewport.addButton(renderer, "A* pathfinding", fillAll, outline );

  outline = { 20, 80, 10 * 14, 18 };
  sideViewport.addButton(renderer, "Spinning globe", fillAll, outline );

  outline = { 20, 100, 10 * 14, 18 };
  sideViewport.addButton(renderer, "Discovery game", fillAll, outline );


vps.push_back(sideViewport);
vps.push_back(mainViewport);
}

// GameOfLife game;
// game.init();

  while(true) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    
    
    screen -> clear();
    
    // Clear renderer
    
    // Check for user events
    events.poll(reRender, &pathfinder, vps);

  mainViewport.render(renderer);
  sideViewport.render(renderer);


    // grid.render(screen -> getRenderer(), pathfinder.getNodes());
    // pathfinder.findPath();
    // // Render
    // target.x = (pathfinder.startNode -> x * SQUARE) + OFFSET;
    // target.y = (pathfinder.startNode -> y * SQUARE) + OFFSET;
    // SDL_SetRenderDrawColor(screen -> getRenderer(), 0, 255, 0, 0);
    // SDL_RenderFillRect(screen -> getRenderer(), &target);
    // target.x = (pathfinder.endNode -> x * SQUARE) + OFFSET;
    // target.y = (pathfinder.endNode -> y * SQUARE) + OFFSET;
    // SDL_SetRenderDrawColor(screen -> getRenderer(), 255, 0, 0, 0);
    // SDL_RenderFillRect(screen -> getRenderer(), &target);


    // vehicle.update(delta);
    // location.x = vehicle.m_vPos.x;
    // location.y = vehicle.m_vPos.y;
    // std::cout << vehicle.m_vPos.y << std::endl;
    // SDL_RenderCopy(screen -> getRenderer(), texture, NULL, &location);

// game of life
  // game.render(renderer);
  // game.setLife();

//perlin
    // if(reRender) 
    // {
    //   perlin.initializeArray1d();
    //   perlin.initialNoise2d[1] = 0.5f; // Set sea level
    //   perlin.render1d(screen -> getRenderer());
    //   reRender = false;
    // }
    // Render to screen
    screen -> render();

    while (SDL_GetTicks() - previous < 500);

    delta = current - previous;
    previous = SDL_GetTicks();
    current = SDL_GetTicks();
  }
  return 0;
}
