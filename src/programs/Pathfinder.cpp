#include "../headers/Pathfinder.h"
#include <list>
#include <limits>
#include "../headers/Constants.h"
#include "../engine/headers/ScreenManager.h"
#include <iostream>

Node::Node()
{
    hasObstacle = false;
    isVisited = false;
    distanceGoal = std::numeric_limits<double>::infinity();
    distanceStart = std::numeric_limits<double>::infinity();
    parentNode = nullptr;
    
}

Pathfinder::Pathfinder()
{
    std::cout << __func__ << std::endl;
    nodes = new Node[WIDTH * HEIGHT];
    initializeNodes();
    startNode = &nodes[1 + 0 * WIDTH];
    endNode = &nodes[47 + 47 * WIDTH];
}

void Pathfinder::initializeNodes()
{
    // Create all possible paths from each node
    for(int i = 0; i < WIDTH; i++)
    {
        for(int j = 0; j < HEIGHT; j++)
        {
            nodes[i + j * WIDTH].x = i;
            nodes[i + j * WIDTH].y = j;
            if(j > 0)
            {
                nodes[i + j * WIDTH].neighbours.push_back(&nodes[i + (j - 1) * WIDTH]);
                if(i > 0)
                    nodes[i + j * WIDTH].neighbours.push_back(&nodes[i - 1 + (j-1) * WIDTH]);
                if(i < WIDTH - 1)   
                    nodes[i + j * WIDTH].neighbours.push_back(&nodes[i + 1 + (j-1) * WIDTH]);
            }
            if(j < HEIGHT - 1)
            {
                nodes[i + j * WIDTH].neighbours.push_back(&nodes[i + (j + 1) * WIDTH]);
                if(i > 0)
                    nodes[i + j * WIDTH].neighbours.push_back(&nodes[i - 1 + (j+1) * WIDTH]);
                if(i < WIDTH - 1)   
                    nodes[i + j * WIDTH].neighbours.push_back(&nodes[i + 1 + (j+1) * WIDTH]);
                
            }
            if(i > 0)           nodes[i + j * WIDTH].neighbours.push_back(&nodes[i - 1 + j * WIDTH]);
            if(i < WIDTH - 1)   nodes[i + j * WIDTH].neighbours.push_back(&nodes[i + 1 + j * WIDTH]);
        }
    }
}
void Pathfinder::resetNodes()
{
    // Create all possible paths from each node
    for(int i = 0; i < WIDTH; i++)
    {
        for(int j = 0; j < HEIGHT; j++)
        {
            nodes[i + j * WIDTH].isVisited = false;
            nodes[i + j * WIDTH].distanceGoal = std::numeric_limits<double>::infinity();
            nodes[i + j * WIDTH].distanceStart = std::numeric_limits<double>::infinity();
            nodes[i + j * WIDTH].parentNode = nullptr;
        }
    }
}

void Pathfinder::findPath()
{
    auto distance = [](Node* a, Node* b)
    {
        return sqrtf((a -> x - b -> x) * 
                     (a -> x - b -> x) + 
                     (a -> y - b -> y) * 
                     (a -> y - b -> y));
    };

    auto heuristic = [distance](Node* a, Node* b)
    {
        return distance(a, b);
    };

    Node* currentNode = startNode;

    startNode -> distanceStart = 0.0f;
    startNode -> distanceGoal = heuristic(startNode, endNode);
    std::list<Node*> untestedNodes;
    untestedNodes.push_back(startNode);

    while(!untestedNodes.empty())
    {

        untestedNodes.sort([](const Node* lhs, const Node* rhs){ return lhs -> distanceGoal < rhs -> distanceGoal; });

        while(!untestedNodes.empty() && untestedNodes.front() -> isVisited)
        {
            untestedNodes.pop_front();
        }
        if(untestedNodes.empty())
        {
            break;
        }
        currentNode = untestedNodes.front();
        currentNode -> isVisited = true;

        for(auto neighbour : currentNode -> neighbours)
        {
            if(!neighbour -> isVisited && !neighbour -> hasObstacle)
                untestedNodes.push_back(neighbour);
            
            float possibleLower = currentNode -> distanceStart + distance(currentNode, neighbour);
            if(possibleLower < neighbour -> distanceStart)
            {
                neighbour -> parentNode = currentNode;
                neighbour -> distanceStart = possibleLower;
                neighbour -> distanceGoal = neighbour -> distanceStart + heuristic(neighbour, endNode);
            }
        }
    }
    render();
}

void Pathfinder::render()
{
    if (endNode != nullptr)
    {
        Node *p = endNode;

        // These should be generalized
        
        SDL_Point cellSize = { SQUARE - OFFSET*2, SQUARE - OFFSET*2 };
        SDL_Rect target = { 0, 0, cellSize.x, cellSize.y };
        SDL_Renderer* renderer = Screen::getRenderer();

        while (p -> parentNode != nullptr)
        {
            //draw connection
            target.x = (p -> x * SQUARE) + OFFSET;
            target.y = (p -> y * SQUARE) + OFFSET;
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            SDL_RenderFillRect(renderer, &target);        
            p = p -> parentNode;
        }
    }
}

void Pathfinder::clicked(SDL_Point* mouse)
{
    int x = mouse->x/SQUARE;
    int y = mouse->y/SQUARE;

    if(nodes[x + y * WIDTH].hasObstacle) nodes[x + y * WIDTH].hasObstacle = false;
    else nodes[x + y * WIDTH].hasObstacle = true;
}
Node* Pathfinder::getNodes()
{
    return nodes;
}
