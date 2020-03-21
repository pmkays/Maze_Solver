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

void MazeSolver::solve(Maze maze) 
{
   findCoordinates(maze, START, coordinatesPtr);
   int startY = coordinatesPtr[Y_COOR_ARRAY];
   int startX = coordinatesPtr[X_COOR_ARRAY];

   std::cout << "Start coordinates"<< std::endl;
   std::cout << startX << std::endl;
   std::cout << startY << std::endl;

   findCoordinates(maze, END, coordinatesPtr);
   int endY = coordinatesPtr[Y_COOR_ARRAY];
   int endX = coordinatesPtr[X_COOR_ARRAY];

   std::cout << "End coordinates"<< std::endl;
   std::cout << endX << std::endl;
   std::cout << endY << std::endl;

   int y = startY;
   int x = startX; 
   
   bool keepLooping = true; 

   while(keepLooping)
   {
      if(!solution->contains(x,y))
      {
         //set breadcrumb at each new position
         Breadcrumb* breadcrumb = new Breadcrumb(x, y, false);
         solution->addCopy(breadcrumb);
      }

      // if(y > 0 && (maze[north][x] == OPEN || maze[north][x] == 'E') && !solution->contains(x,north))
      // {
      //    std::cout << "North" << std::endl; 
      //    y--;
      // }
      // else if(x < 20 && (maze[y][east] == OPEN || maze[y][east] == 'E') && !solution->contains(east,y))
      // {
      //    std::cout << "East" << std::endl;
      //    x++;
      // }
      // else if(y < 20 && (maze[south][x] == OPEN || maze[y][south] == 'E') && !solution->contains(x,south))
      // {
      //    std::cout << "South" << std::endl;
      //    y++;
      // }
      // else if(x > 0 && (maze[y][west] == OPEN || maze[y][west] == 'E') && !solution->contains(west,y))
      // {
      //    std::cout << "West" << std::endl;
      //    x--;
      // }
      if(y > 0 && (NORTH_MAZE == OPEN || NORTH_MAZE == 'E') && !solution->contains(x,NORTH_COOR))
      {
         std::cout << "North" << std::endl; 
         y--;
      }
      else if(x < 20 && (EAST_MAZE == OPEN || EAST_MAZE == 'E') && !solution->contains(EAST_COOR,y))
      {
         std::cout << "East" << std::endl;
         x++;
      }
      else if(y < 20 && (SOUTH_MAZE == OPEN || SOUTH_MAZE == 'E') && !solution->contains(x,SOUTH_COOR))
      {
         std::cout << "South" << std::endl;
         y++;
      }
      else if(x > 0 && (WEST_MAZE == OPEN || WEST_MAZE == 'E') && !solution->contains(WEST_COOR,y))
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
                coordinatesPtr[Y_COOR_ARRAY] = rows;
                coordinatesPtr[X_COOR_ARRAY] = cols; 
            }
        }
    }
}