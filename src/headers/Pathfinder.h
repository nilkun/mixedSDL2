#ifndef NODE_ASTAR_H_
#define NODE_ASTAR_H_
#include <vector>
#include <SDL2/SDL.h>
#include "Constants.h"


struct Node {
    Node();
    bool hasObstacle;
    bool isVisited;
    float distanceGoal;
    float distanceStart;
    int x;
    int y;
    std::vector<Node*> neighbours;
    Node* parentNode;    
};

class Pathfinder
{

public:
    Pathfinder();
    void initializeNodes();
    void findPath();
    void clicked(SDL_Point* mouse);
    void render();
    void resetNodes();
    Node* getNodes();
    
    //public due to main
    Node* startNode;
    Node* endNode;

private:
    Node* nodes;
    int width;
    int height;

};


// render nodes
// get node from mouse
// draw connections 
// set start and end node


// dist x+y/2 instead of hypo


// Node nodeEnd;
// if (nodeEnd != nullptr)
// {
//     Node *p = nodeEnd;
//     while p -> parent != nullptr
//     {
//         //draw connection

//         p = p -> parent;
//     }
// }

#endif