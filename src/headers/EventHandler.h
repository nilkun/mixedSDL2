#ifndef __EVENTHANDLER_H__
#define __EVENTHANDLER_H__
#include <SDL2/SDL.h>
#include "Pathfinder.h"
#include <vector>
#include "Viewport.h"

class EventHandler{

  SDL_Point mouse = { 0, 0 };
public:
  SDL_Event event;
  EventHandler();
  void poll(bool &reRender, Pathfinder *pathfinder, std::vector<Viewport> vps);
};

#endif