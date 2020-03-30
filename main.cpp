/*
*   ANALYSIS - s3782041 - Paula Kurniawan
*
*   Approach:    When implementing, I made sure to follow specifications slowly and divide the assignment into sub-problems
*                that I tackled one by one. E.g. breaking apart the algorithm. I started off with implementing the
*                Breadcrumb and Trail classes before working on Mazesolver and used the already given tests in Main to help.
*                I then created my own tests and from there just worked on the program little by little as we learnt more about
*                C++ features weekly.
*   Issues:      I had some trouble implementing the backtracking algorithm, as I originally made an error when travelling to the
*                next breadcrumb which lead to the output of my maze to be incorrect. I also wasn't sure what a deep copy or adding
*                a copy meant initially which caused confusion.                
*   Choices:     When making objects, I usually made them as pointers stored on the heap because it provided greater flexibility. For
*                changing primitives, e.g. coordinates between methods, I usually passed by reference as that was personally easier for me.
*   Efficiency:  I think overall the efficiency of my program is not the worst but also not the best. Because the maze array has fixed
*                dimensions, the trail and directions (milestone3) are always set to have a max of 400 elements which means that a lot
*                of memory is allocated for these arrays. It would be better if we had some sort of dynamic data structure instead.
*   Milestone 3: I implemented milestones 1, 2 and 3. I completed milestone 3 by utilising an array of strings and then also returning
*                this in the main and then printing it to display the direcitons. The directions are added/removed in accordance 
*                to the direction conditionals and backtrack method in MazeSolver.
*
*/

#include <iostream>
#include <string>

#include "Types.h"
#include "MazeSolver.h"

// Helper test functions
void testBreadcrumb();
void testTrail();

// Read a maze from standard input.
void readMazeStdin(Maze maze);

// Print out a Maze to standard output.
void printMazeStdout(Maze maze, Trail* solution);

void printDirections(std::string* directions, int directionsSize);

int main(int argc, char** argv) {
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!

    // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // testBreadcrumb();
    // testTrail();
    // std::cout << "DONE TESTING" << std::endl << std::endl;

    // Load Maze from stdin
    Maze maze;
    readMazeStdin(maze);

    // Solve using MazeSolver
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2

    MazeSolver* solver = new MazeSolver();
    Trail* solution = nullptr;
    std::string* directions = nullptr;
    int directionsSize = 0; 

    solver->solve(maze);
    solution = solver->getSolution();
    directions = solver->getDirections();
    directionsSize = solver->getDirectionsSize();

    // Print Maze to stdout
    printMazeStdout(maze, solution);

    printDirections(directions, directionsSize);

    delete solver;
    
    return EXIT_SUCCESS;
}

void readMazeStdin(Maze maze) 
{
    // ASSUME THE MAZE IS A FIXED SIZE (20X20).
    while(!std::cin.eof())
    {
        for(int i = 0; i < MAZE_DIM ; i++)
        {
            for(int j = 0; j < MAZE_DIM; j++)
            {
                std::cin >> maze[i][j]; 
            }
        }
    }     
}

void printMazeStdout(Maze maze, Trail* solution) 
{
    for(int y = 0; y < MAZE_DIM; y++)
    {
        for(int x = 0; x <MAZE_DIM; x++)
        {
            if(solution->contains(x, y) && !solution->containsStale(x,y) && maze[y][x] != 'S')
            {
                maze[y][x] = '*'; 
            }
        }
    }

    for(int y = 0; y < MAZE_DIM ; y++)
    {
        for(int x = 0; x < MAZE_DIM ; x++)
        {
            std::cout <<  maze[y][x]; 
        }
        std::cout << std::endl; 
    }
}

void printDirections(std::string* directions, int directionsSize)
{
    for(int i = 0; i < directionsSize; i++)
    {
        std::cout<< directions[i] << std::endl;
    }
}

void testBreadcrumb() {
    std::cout << "TESTING BREADCRUMB" << std::endl;

    // Make a breadcrumb and print out the contents
    Breadcrumb* breadcrumb = new Breadcrumb(1, 1, false);
    std::cout << breadcrumb->getX() << ",";
    std::cout << breadcrumb->getY() << ",";
    std::cout << breadcrumb->isStale() << std::endl;

    // Change breadcrumb stale-ness and print again
    breadcrumb->setStale(true);
    std::cout << breadcrumb->getX() << ",";
    std::cout << breadcrumb->getY() << ",";
    std::cout << breadcrumb->isStale() << std::endl;
}

void testTrail() {
    std::cout << "TESTING TRAIL" << std::endl;

    // Make a simple trail, should be empty size
    Trail* trail = new Trail();
    std::cout << "Trail size: " << trail->size() << std::endl;

    // Add a breadcrumb to the trail, print size, check contains
    Breadcrumb* b1 = new Breadcrumb(1, 1, false);
    trail->addCopy(b1);
    std::cout << "Trail size: " << trail->size() << std::endl;
    std::cout << "Contains (0,0): " << trail->contains(0,0) << std::endl;
    std::cout << "Contains (1,1): " << trail->contains(1,1) << std::endl;

    // Add second breadcrumb
    Breadcrumb* b2 = new Breadcrumb(0, 0, true);
    trail->addCopy(b2);
    std::cout << "Trail size: " << trail->size() << std::endl;
    std::cout << "Contains (0,0): " << trail->contains(0,0) << std::endl;
    std::cout << "Contains (1,1): " << trail->contains(1,1) << std::endl;

    // Test Get-ith - should be 0,0,true
    Breadcrumb* getB = trail->getPtr(1);
    std::cout << getB->getX() << ",";
    std::cout << getB->getY() << ",";
    std::cout << getB->isStale() << std::endl;

    // Print out the trail
    std::cout << "PRINTING OUT A TRAIL IS AN EXERCISE FOR YOU TO DO" << std::endl;
}
