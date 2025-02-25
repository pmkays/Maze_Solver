
#ifndef COSC_ASS_ONE_PARTICLE_FILTER
#define COSC_ASS_ONE_PARTICLE_FILTER

#include "Breadcrumb.h"
#include "Trail.h"
#include "Types.h"

class MazeSolver {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */


   // Constructor/Destructor
   MazeSolver();
   ~MazeSolver();

   // Solve the maze
   void solve(Maze maze);

   // Get a DEEP COPY of the solution
   Trail* getSolution();

   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */

   //backtracks if there is a deadend
   void backTrack(int length, int& x, int& y, int startX, int startY);

   //used to locate start/end points
   void findCoordinates(Maze maze, char letter, int* coordinatesPtr);

   //number of directions in array
   int getDirectionsSize();

   //returns directions array for main
   std::string* getDirections();

private:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */

   // Trail of breadcrumbs from the start to end
   Trail* solution;


   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */
   
   //keep x and y coordinates together
   int coordinates[2];
   
   //copy trail to get deep copy
   Trail* copySolution;

   //represents the directions taken to get out of maze
   std::string* directions;

   //how many directions have been stored
   int directionsSize;
};

#endif // COSC_ASS_ONE_PARTICLE_FILTER
