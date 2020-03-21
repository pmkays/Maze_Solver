#include <iostream>
#include <string>


#include "MazeSolver.h"



MazeSolver::MazeSolver() 
{
   coordinates[2] = {};
   coordinatesPtr = coordinates;
   solution = new Trail();
}

MazeSolver::~MazeSolver() 
{
   delete solution;

   //delete breadcrumbs?
}

#define north     y - 1
#define east      x + 1
#define south     y + 1
#define west      x - 1


void MazeSolver::solve(Maze maze) 
{
   findCoordinates(maze, 'S', coordinatesPtr);
   int startY = coordinatesPtr[0];
   int startX = coordinatesPtr[1];

   std::cout << "Start coordinates"<< std::endl;
   std::cout << startX << std::endl;
   std::cout << startY << std::endl;

   findCoordinates(maze, 'E', coordinatesPtr);
   int endY = coordinatesPtr[0];
   int endX = coordinatesPtr[1];

   std::cout << "End coordinates"<< std::endl;
   std::cout << endX << std::endl;
   std::cout << endY << std::endl;

   int y = startY;
   int x = startX; 
   
   bool keepLooping = true; 

   // char north = maze[y - 1][x];
   // char east = maze[y][x + 1];
   // char south = maze[y + 1][x];
   // char west = maze[y][x - 1];

   while(keepLooping)
   {
      if(!solution->contains(x,y))
      {
         //set breadcrumb at each new position
         Breadcrumb* breadcrumb = new Breadcrumb(x, y, false);
         solution->addCopy(breadcrumb);
      }

      if(y > 0 && (maze[north][x] == OPEN || maze[north][x] == 'E') && !solution->contains(x,north))
      {
         std::cout << "North" << std::endl; 
         y--;
      }
      else if(x < 20 && (maze[y][east] == OPEN || maze[y][east] == 'E') && !solution->contains(east,y))
      {
         std::cout << "East" << std::endl;
         x++;
      }
      else if(y < 20 && (maze[south][x] == OPEN || maze[y][south] == 'E') && !solution->contains(x,south))
      {
         std::cout << "South" << std::endl;
         y++;
      }
      else if(x > 0 && (maze[y][west] == OPEN || maze[y][west] == 'E') && !solution->contains(west,y))
      {
         std::cout << "West" << std::endl;
         x--;
      }
      // else
      // {
      //    solution->getPtr(solution->size())->setStale(true);
      // }

      std::cout << "Current position"<< std::endl;
      std::cout << x << std::endl;
      std::cout << y << std::endl;

      
      if(x == endX && y == endY)
      {
         keepLooping = false;
      }
   }
}

Trail* MazeSolver::getSolution() {
   // TODO
   return nullptr;
}

void MazeSolver::findCoordinates(Maze maze, char letter, int* coordinatesPtr)
{
    for(int rows = 0; rows < MAZE_DIM; rows++)
    {
        for(int cols = 0; cols < MAZE_DIM; cols++)
        {
            if(maze[rows][cols] == letter)
            {
                coordinatesPtr[0] = rows;
                coordinatesPtr[1] = cols; 
            }
        }
    }
}