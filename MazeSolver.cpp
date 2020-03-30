#include <iostream>
#include <string>


#include "MazeSolver.h"

//maze-related navigation
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

#define COOR_PAIR       2
#define Y_COOR_ARRAY    0
#define X_COOR_ARRAY    1

//for boundaries and/or limits
#define ZERO_BOUND      0
#define ONE_BEFORE      1
#define TWO_BEFORE      2
#define MIN_LENGTH      0

MazeSolver::MazeSolver() 
{
   coordinates[COOR_PAIR] = {};
   solution = new Trail();
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
   std::string north = "north";
   std::string east = "east";
   std::string south = "south";
   std::string west = "west";
   
   findCoordinates(maze, START, coordinates);
   int startY = coordinates[Y_COOR_ARRAY];
   int startX = coordinates[X_COOR_ARRAY];

   findCoordinates(maze, END, coordinates);
   int endY = coordinates[Y_COOR_ARRAY];
   int endX = coordinates[X_COOR_ARRAY];

   int y = startY;
   int x = startX; 
   
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

      //checks what direction to go and backtracks if necessary
      if(y > ZERO_BOUND && (NORTH_MAZE == OPEN || NORTH_MAZE == END) && !solution->contains(x,NORTH_COOR))
      {
         y--;
         directions[directionsSize] = north;
      }
      else if(x < MAZE_DIM - ONE_BEFORE && (EAST_MAZE == OPEN || EAST_MAZE == END) && !solution->contains(EAST_COOR,y))
      {
         x++;
         directions[directionsSize] = east;
      }
      else if(y < MAZE_DIM - ONE_BEFORE && (SOUTH_MAZE == OPEN || SOUTH_MAZE == END) && !solution->contains(x,SOUTH_COOR))
      {
         y++;
         directions[directionsSize] = south;
      }
      else if(x > ZERO_BOUND && (WEST_MAZE == OPEN || WEST_MAZE == END) && !solution->contains(WEST_COOR,y))
      {
         x--;
         directions[directionsSize] = west;
      }
      else
      {
         backTrack(solution->size(), x, y, startX, startY);
      }

      //stopping condition when we get to the end
      if(x == endX && y == endY)
      {
         keepLooping = false;
      }

      //increase our direction counter as we go
      directionsSize++;
   }
}

Trail* MazeSolver::getSolution() 
{
   Trail* copySolution = new Trail(*solution);
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

void MazeSolver::findCoordinates(Maze maze, char letter, int coordinates[])
{
    for(int y = 0; y < MAZE_DIM; y++)
    {
        for(int x = 0; x < MAZE_DIM; x++)
        {
            if(maze[y][x] == letter)
            {
                coordinates[Y_COOR_ARRAY] = y;
                coordinates[X_COOR_ARRAY] = x; 
            }
        }
    }
}

void MazeSolver::backTrack(int length, int& x, int& y, int startX, int startY)
{
   length--;

   if(!solution->getPtr(length)->isStale())
   {
      //make current breadcrumb stale as long as it's not the start breadcrumb
      if(length != MIN_LENGTH)
      {
         solution->getPtr(length)->setStale(true);
      }

      if(length > MIN_LENGTH)
      {
         /*
         * reduce the directionsSize by 2 so it can be overridden with the next move
         * reduce by 2 because it will increase by 1 again when it returns
         */
         directionsSize -= TWO_BEFORE; 
         x = solution->getPtr(length - ONE_BEFORE)->getX(); 
         y = solution->getPtr(length - ONE_BEFORE)->getY();
      }
      else
      {
         //if we are at start breadcrumb
         x = solution->getPtr(length)->getX(); 
         y = solution->getPtr(length)->getY();
         directionsSize = -ONE_BEFORE;
      }

   }
   else
   {
      //keep recursively calling the function until the last good breadcrumb is found
      MazeSolver::backTrack(length, x, y, startX, startY);
   }  
}