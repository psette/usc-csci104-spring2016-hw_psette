#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include "maze.h"
#include "heap.h"
#include "visitedtracker.h"

/*
 * I didn't want the students to have to deal
 * with function pointers, so I'm making the
 * MazeSolver an object with various solve
 * methods.
 *
 * I won't be offended if anyone wants to refactor
 * this to make specific functions for them to call.
 */


class MazeDisplay;
class Maze;

class MazeSolver
{
public:
    MazeSolver(Maze * m, MazeDisplay * md);

    void solveByBFS();

    void solveByDFSIterative();

    void solveByDFSRecursive();

    void solveByAStar(int heuristicChoice);

private:
	bool DFSRecursiveHelper(int, int, VisitedTracker&, std::vector<Direction>&);
    int squareNumber(int r, int c) const;
    std::vector<Direction> path;
    Maze * maze;
    MazeDisplay * display;
    int numExplored_DFS = 0;
};

#endif // MAZESOLVER_H
