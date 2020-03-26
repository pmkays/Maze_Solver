#include <iostream>
#include <string>


#include "MazeSolver.h"

#define NORTH_COOR     y - 1
#define EAST_COOR      x + 1
#define SOUTH_COOR     y + 1
#define WEST_COOR      x - 1

#define NORTH_MAZE     maze[NORTH_COOR][x]
#define EAST_MAZE      maze[y][EAST_COOR]
#define SOUTH_MAZE     maze[SOUTH_COOR][x]
#define WEST_MAZE      maze[y][WEST_COOR]

#define START          'S'
#define END            'E'

#define Y_COOR_ARRAY          0
#define X_COOR_ARRAY          1

MazeSolver::MazeSolver() 
{
   coordinates[2] = {};
   coordinatesPtr = coordinates;
   solution = new Trail();
   copySolution = new Trail();
   directions = new std::string[TRAIL_ARRAY_MAX_SIZE];
   directionsSize = 0; 
}

MazeSolver::~MazeSolver() 
{
   delete solution;
   delete copySolution; 
   delete[] directions;
}

void MazeSolver::solve(Maze maze) 
{
   std::string north = "North";
   std::string east = "East";
   std::string south = "South";
   std::string west = "West";
   
   findCoordinates(maze, START, coordinatesPtr);
   int startY = coordinatesPtr[Y_COOR_ARRAY];
   int startX = coordinatesPtr[X_COOR_ARRAY];

   findCoordinates(maze, END, coordinatesPtr);
   int endY = coordinatesPtr[Y_COOR_ARRAY];
   int endX = coordinatesPtr[X_COOR_ARRAY];

   int y = startY;
   int x = startX; 

   // std::cout << "Start coordinates"<< std::endl;
   // std::cout << startX << std::endl;
   // std::cout << startY << std::endl;

   // std::cout << "End coordinates"<< std::endl;
   // std::cout << endX << std::endl;
   // std::cout << endY << std::endl;
   
   bool keepLooping = true; 

   while(keepLooping)
   {
      //if there isn't a breadcrumb in this position
      if(!solution->contains(x,y))
      {
         //set breadcrumb at each new position
         Breadcrumb* breadcrumb = new Breadcrumb(x, y, false);
         solution->addCopy(breadcrumb);
      }

      if(y > 0 && (NORTH_MAZE == OPEN || NORTH_MAZE == END) && !solution->contains(x,NORTH_COOR))
      {
         y--;
         directions[directionsSize] = north;
      }
      else if(x < 19 && (EAST_MAZE == OPEN || EAST_MAZE == END) && !solution->contains(EAST_COOR,y))
      {
         x++;
         directions[directionsSize] = east;
      }
      else if(y < 19 && (SOUTH_MAZE == OPEN || SOUTH_MAZE == END) && !solution->contains(x,SOUTH_COOR))
      {
         y++;
         directions[directionsSize] = south;
      }
      else if(x > 0 && (WEST_MAZE == OPEN || WEST_MAZE == END) && !solution->contains(WEST_COOR,y))
      {
         x--;
         directions[directionsSize] = west;
      }
      else
      {
         backTrack(solution->size(), x, y, startX, startY);

      }

      // std::cout << "Current position"<< std::endl;
      // std::cout << x << std::endl;
      // std::cout << y << std::endl;
      // std::cout << "---_-" << std::endl;

      if(x == endX && y == endY)
      {
         keepLooping = false;
      }

      directionsSize++;
   }
}

Trail* MazeSolver::getSolution() 
{
   for(int i = 0; i < solution->size(); i++)
   {
      Breadcrumb* copyCrumb = solution->getPtr(i);
      copySolution->addCopy(copyCrumb);
   }
   return copySolution;
}

std::string* MazeSolver::getDirections()
{
   return directions;
}

int MazeSolver::getDirectionsSize()
{
   return directionsSize;
}

void MazeSolver::findCoordinates(Maze maze, char letter, int* coordinatesPtr)
{
    for(int y = 0; y < MAZE_DIM; y++)
    {
        for(int x = 0; x < MAZE_DIM; x++)
        {
            if(maze[y][x] == letter)
            {
                coordinatesPtr[Y_COOR_ARRAY] = y;
                coordinatesPtr[X_COOR_ARRAY] = x; 
            }
        }
    }
}

void MazeSolver::backTrack(int length, int& x, int& y, int startX, int startY)
{
   length--;

   // std::cout << "Length: " << length << std::endl;
   // std::cout << "Breadcrumb x: " << solution->getPtr(length)->getX() << std::endl;
   // std::cout << "Breadcrumb x: " << solution->getPtr(length)->getY() << std::endl;
   // std::cout << "Is breadcrumb stale? " << solution->getPtr(length)->isStale() << std::endl;



   // check for the most recent good breadcrumb
   if(!solution->getPtr(length)->isStale())
   {
      //make current breadcrumb stale as long as it's not the start breadcrumb
      if(length!=0)
      {
         solution->getPtr(length)->setStale(true);
      }

      // std::cout << "x: " << x << std::endl;
      // std::cout << "y: " << y << std::endl;
      if(length > 0)
      {
         //reduce the directionsSize by 2 so it can be overridden with the next move
         //reduce by 2 because it will increase by 1 again when it returns to the main function call
         directionsSize-=2; 
         x = solution->getPtr(length - 1)->getX(); 
         y = solution->getPtr(length - 1)->getY();
      }
      else
      {
         //if we are at the very first breadcrumb, i.e. the start
         //then we stay there so that we can traverse alternative paths
         //as there MUST be a valid path somewhere from the start
         x = solution->getPtr(length)->getX(); 
         y = solution->getPtr(length)->getY();
         directionsSize = -1;
      }

   }
   else
   {
      //keep recursively calling the function until the last good breadcrumb is found
      MazeSolver::backTrack(length, x, y, startX, startY);
   }  
}