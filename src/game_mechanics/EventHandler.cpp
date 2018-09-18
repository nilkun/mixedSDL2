#include "../headers/EventHandler.h"
#include "../headers/Perlin.h"
#include <iostream>

EventHandler::EventHandler() {  };
void EventHandler::poll(bool &reRender, Pathfinder *pathfinder, std::vector<Viewport> vps)
{
  while(SDL_PollEvent(&event)) 
  {
    switch (event.type) 
    {
      case SDL_QUIT: 
      {
        exit(1);
      }

      case SDL_MOUSEBUTTONDOWN:
      {
        switch (event.button.button)
        {
          case SDL_BUTTON_LEFT:
          {
            SDL_GetMouseState(&mouse.x, &mouse.y);
            pathfinder -> clicked(&mouse);
            pathfinder -> resetNodes();
          for(auto vp : vps){            vp.click(mouse);}

            Perlin::octave++;
            if(Perlin::octave >=8) Perlin::octave=1;
            break;
          }
        }
      }
    //       case SDL_BUTTON_RIGHT:
    //       {
    //          SDL_GetMouseState(&mouse.x, &mouse.y);
    //          Messages::send("Right click");
    //          game -> selectedObject -> mouseMove(mouse);
    //          break;
    //       }
    //     }

    case SDL_KEYDOWN:
      switch(event.key.keysym.sym)
      {
    //       case SDLK_ESCAPE:
    //       {
    //         exit(1);
    //       }
    //       case SDLK_w:
    //       {
    //         GameWorld::changeOffset(0, -2);
    //         break;
    //       } 
    //       case SDLK_s:
    //       {
    //         GameWorld::changeOffset(0, 2);
    //         break;
    //       }  
    //       case SDLK_a:
    //       {
    //         GameWorld::changeOffset(-2, 0);
    //         break;
    //       }
    //       case SDLK_d:
    //       {
    //         GameWorld::changeOffset(2, 0);
    //         break;
    //       }
    //       case SDLK_z:
    //       {
    //         GameWorld::zoom(2);
    //         break;
    //       }
    //       case SDLK_x:
    //       {
    //         GameWorld::zoom(-2);
    //         break;
    //       }
          case SDLK_UP:
          {
            std::cout << "up!" << std::endl;
            Perlin::scale += 0.2;
            break;
          }
          case SDLK_DOWN:
          {
            Perlin::scale -= 0.2;
            if(Perlin::scale < 0.2) Perlin::scale = 0.2;
            break;
          }
          case SDLK_SPACE:
          {
            std::cout <<"SPACE!!!" << std::endl;
            reRender = true;
            break;
          }
    //       case SDLK_LEFT:
    //       {
    //         game -> selectedObject -> move(WEST);
    //         break;
    //       }
    //       case SDLK_RIGHT:
    //       {
    //         game -> selectedObject -> move(EAST);
    //         break;
    //       }
    //       case SDLK_b:
    //       {
    //         // ui -> addMessage("Making camp...");
    //         game -> currentPlayer -> addSettlement(game -> selectedObject -> position);
    //         // Game::getInstance() -> player -> addSettlement();
    //         break;
    //       }
    //       case SDLK_e:
    //       {
    //         GameManager::endturn();
    //         break;
    //       } 
         }
    }
  }
}



