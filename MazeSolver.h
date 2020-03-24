
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

   void backTrack(int length, int& x, int& y, int& directionsCount);
   void backTrack(int length, int& x, int& y);
   void findCoordinates(Maze maze, char letter, int* coordinatesPtr);

   int getDirectionsSize();

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
   int coordinates[2];
   int* coordinatesPtr;
   Trail* copySolution;
   std::string* directions;
   int directionsSize;
};

#endif // COSC_ASS_ONE_PARTICLE_FILTER
