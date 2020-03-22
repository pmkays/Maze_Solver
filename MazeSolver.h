
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

   void backTrack(int length, Maze maze, int& x, int& y);
   void backTrack2(int& x, int& y);
   void findCoordinates(Maze maze, char letter, int* coordinatesPtr);
private:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */

   // Trail of breadcrumbs from the start to end
   Trail* solution;


   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */
   int coordinates[2];
   int* coordinatesPtr;

   Trail* copySolution;
};

#endif // COSC_ASS_ONE_PARTICLE_FILTER
