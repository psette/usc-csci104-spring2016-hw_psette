#include "mazesolver.h"
#include "mazedisplay.h"
#include "visitedtracker.h"
#include <QMessageBox>
#include <queue>
#include <stack>
#include <vector>
#include <cmath>
#include <iostream>
MazeSolver::MazeSolver(Maze * m, MazeDisplay * md): maze(m), display(md){}
bool MazeSolver::DFSRecursiveHelper(int r, int c, VisitedTracker& visited,std::vector<Direction>& ref){
    if( maze->getStartCol() == c && maze->getStartRow() == r) return true;
    if ( maze->canTravel(UP, r, c) && ! visited.isVisited(r-1,c)){
        ref[squareNumber(r-1, c)] = DOWN;
        visited.setVisited(r-1,c);
        if ( DFSRecursiveHelper(r-1,c,visited,ref)) {
            path.push_back(ref[squareNumber(r-1,c)]);
            numExplored_DFS++;
            return true;
        }
    }
    if ( maze->canTravel(DOWN, r, c) && ! visited.isVisited(r+1,c) ){
        ref[squareNumber(r+1, c)] = UP;
        visited.setVisited(r+1, c);
        if ( DFSRecursiveHelper(r+1,c,visited,ref)){
            path.push_back(ref[squareNumber(r+1,c)]);
            numExplored_DFS++;
            return true;
        }
    }
    if ( maze->canTravel(LEFT, r, c) && ! visited.isVisited(r,c-1) ){
        ref[squareNumber(r, c-1)] = RIGHT;
        visited.setVisited(r, c-1);
        if ( DFSRecursiveHelper(r,c-1,visited,ref)){
            path.push_back(ref[squareNumber(r,c-1)]);
            numExplored_DFS++;
            return true;            
        }
     }
    if ( maze->canTravel(RIGHT, r, c) && ! visited.isVisited(r, c+1) ){
        ref[squareNumber(r, c+1)] = LEFT;
        visited.setVisited(r, c+1);
        if ( DFSRecursiveHelper(r,c+1,visited,ref)){
            path.push_back(ref[squareNumber(r,c+1)]);
            numExplored_DFS++;
            return true;
        }
    }
    return false;
}
void MazeSolver::solveByDFSRecursive(){   
    VisitedTracker visited(maze->numRows(), maze->numCols());
    std::vector<Direction> ref( maze->numRows() * maze->numCols() ); 
    if(DFSRecursiveHelper(maze->getGoalRow(),maze->getGoalCol(),visited,ref))
        display->reportSolution(path, visited, numExplored_DFS);
    path.clear();
}
void MazeSolver::solveByAStar(int choice){
    std::vector<Direction> parent( maze->numRows() * maze->numCols() );
    int rows = maze->numRows(), cols = maze->numCols();
    int rowsFinal = maze->getGoalRow(), colFinal = maze->getGoalCol();
    int** h = new int*[rows];
    int** distances = new int*[rows];
    int r, c, numExplored = 0;
    VisitedTracker vt(maze->numRows(), maze->numCols());
    switch (choice){
        case 2:{
           // A* with Manhattan;
            for(int i = 0; i < rows; ++i){
                h[i] = new int[cols];
                distances[i] = new int[cols];
                for(int j = 0; j < cols; ++j) {
                    distances[i][j] = -1;
                    h[i][j] = std::abs(i - rowsFinal) + std::abs(j - colFinal);
                }
            }
            break;
        }
        case 3:{
        //   A* with Euclidean;
                for(int i = 0; i < rows; ++i){
                    h[i] = new int[cols];
                    distances[i] = new int[cols];
                for(int j = 0; j < cols; ++j) {
                    distances[i][j] = -1;
                    h[i][j] = pow(pow(i - rowsFinal, 2) + pow(j - colFinal, 2), .5);
                }
            }
            break;
        }
        default:{
        //  A* with return 0;
                for(int i = 0; i < rows; ++i){
                    h[i] = new int[cols];
                    distances[i] = new int[cols];
                for(int j = 0; j < cols; ++j) {
                    distances[i][j] = -1;
                    h[i][j] = 0;
                }
            }
            break;
        }
    }
    distances[maze->getStartRow()][maze->getStartRow()] = 0;
    MinHeap<std::pair<int, int>> pq(2);
    pq.add(std::pair<int,int>(maze->getStartRow(), maze->getStartCol() ), 0);
    while( !pq.isEmpty() ) {
        numExplored++;
        std::pair<int,int> v = pq.peek();
        r = v.first;
        c = v.second;
        pq.remove();
        if( r == maze->getGoalRow() && c == maze->getGoalCol() ){
            std::vector<Direction> path;
            std::stack<Direction> st;
            while( r != maze->getStartRow() || c != maze->getStartCol()){
                st.push( parent[ squareNumber(r,c) ]);
                switch( st.top() ){
                case UP: r++; break;
                case DOWN: r--; break;
                case LEFT: c++; break;
                case RIGHT: c--; break;
                }
            }
            while ( ! st.empty() ){
                path.push_back(st.top());
                st.pop();
            }
            display->reportSolution(path, vt, numExplored);
            for(int i = 0; i < rows; ++i){
                delete [] distances[i]; 
                delete [] h[i];
            }
            delete h;
            delete distances;
            return;
        }
        if( maze->canTravel(RIGHT, r, c) && ! vt.isVisited(r,c+1) ){
            distances[r][c + 1] = distances[r][c] + 1; 
            parent[squareNumber(r, c + 1)] = RIGHT;
            vt.setVisited(r, c + 1);
            std::pair<int,int> AddIn;
            AddIn.first = r;
            AddIn.second = c + 1;
            pq.add(AddIn, distances[r][c] + h[r][c+1]);
        }
        if( maze->canTravel(LEFT, r, c) && ! vt.isVisited(r,c-1)){
            distances[r][c - 1] = distances[r][c] + 1; 
            parent[squareNumber(r, c - 1)] = LEFT;
            vt.setVisited(r, c - 1);
            std::pair<int,int> AddIn;
            AddIn.first = r;
            AddIn.second = c - 1;
            pq.add(AddIn, distances[r][c] + h[r][c-1]);
        } 
        if( maze->canTravel(DOWN, r, c) && ! vt.isVisited(r+1,c)){
            distances[r + 1][c] = distances[r][c] + 1; 
            parent[squareNumber(r + 1, c)] = DOWN;
            vt.setVisited(r + 1, c);
            std::pair<int,int> AddIn;
            AddIn.first = r + 1;
            AddIn.second = c;
            pq.add(AddIn, distances[r][c] + h[r + 1][c]);
        } 
        if( maze->canTravel(UP, r, c) && ! vt.isVisited(r-1,c) ){
            distances[r - 1][c] = distances[r][c] + 1; 
            parent[squareNumber(r - 1, c)] = UP;
            vt.setVisited(r - 1,c);
            std::pair<int,int> AddIn;
            AddIn.first = r - 1;
            AddIn.second = c;
            pq.add(AddIn, distances[r][c] + h[r - 1][c]);
        }
    }
}
void MazeSolver::solveByDFSIterative(){
    int r, c;
    int numSquares = maze->numRows() * maze->numCols();
    VisitedTracker vt(maze->numRows(), maze->numCols());

    std::vector<Direction> parent( numSquares ); // what was my immediate prior direction to get here?
    int numExplored = 0;
    vt.setVisited(maze->getStartRow(), maze->getStartCol());
    std::stack<std::pair<int, int>> q;
    q.push(std::pair<int,int>(maze->getStartRow(), maze->getStartCol()));
    while( ! q.empty() )
    {
        std::pair<int, int> v = q.top();
        q.pop();
        numExplored++;

        r = v.first;
        c = v.second;

        /* This one if statement is different from the pseudo-code provided
           in lecture, because we want to stop when we've reached the goal.
           The code provided in lecture was for if you wanted to do a BFS
           that explored the entire graph.
        */
        if( r == maze->getGoalRow() && c == maze->getGoalCol() )
        {
            std::vector<Direction> path;
            std::stack<Direction> st;

            while( r != maze->getStartRow() || c != maze->getStartCol())
            {
                st.push( parent[ squareNumber(r,c) ]);
                switch( st.top() )
                {
                case UP: r++; break; // yes, r++.  I went up to get here...
                case DOWN: r--; break;
                case LEFT: c++; break;
                case RIGHT: c--; break;
                }
            }
            while ( ! st.empty() )
            {
                path.push_back(st.top());
                st.pop();
            }
            display->reportSolution(path, vt, numExplored);
            return;
        }

        /*
         * Now we're back to code that looks like the pseudo-code you've seen.
         * The difference here is that we aren't keeping track of distances;
           that's similar to the difference above.  You could add, and ignore,
           the vector that would result if you wanted to do so.
         */
        if ( maze->canTravel(UP, r, c) && ! vt.isVisited(r-1,c))
        {
            parent[squareNumber(r-1, c)] = UP;
            vt.setVisited(r-1,c);
            q.push(std::pair<int,int>(r-1, c));
        }
        // Note:  this is NOT "else if" ...
        if ( maze->canTravel(DOWN, r, c) && ! vt.isVisited(r+1,c) )
        {
            parent[squareNumber(r+1, c)] = DOWN;
            vt.setVisited(r+1, c);
            q.push(std::pair<int,int>(r+1, c));
        }
        if ( maze->canTravel(LEFT, r, c) && ! vt.isVisited(r,c-1) )
        {
            parent[squareNumber(r, c-1)] = LEFT;
            vt.setVisited(r, c-1);
            q.push(std::pair<int,int>(r, c-1));
        }
        if ( maze->canTravel(RIGHT, r, c) && ! vt.isVisited(r, c+1) )
        {
            parent[squareNumber(r, c+1)] = RIGHT;
            vt.setVisited(r, c+1);
            q.push(std::pair<int,int>(r, c+1));
        }
    }
}

void MazeSolver::solveByBFS()
{
    /* In lecture on Tuesday March 22, we had a graph
       with vertices numbered 0 to n-1, inclusive.
       Instead, we have vertices with two numbers,
       row and col, in the range:
       [0, maze->numRows()-1], [0, maze->numCols() -1 ]
       to assign each a unique number [0, maze->numRows() * maze->numCols() -1]
       we will say that maze square (r,c) is really number
       r * maze->numCols() + c
    */
    int r, c;
    int numSquares = maze->numRows() * maze->numCols();
    VisitedTracker vt(maze->numRows(), maze->numCols());

    std::vector<Direction> parent( numSquares ); // what was my immediate prior direction to get here?
    int numExplored = 0;
    vt.setVisited(maze->getStartRow(), maze->getStartCol());
    std::queue<std::pair<int, int>> q;
    q.push(std::pair<int,int>(maze->getStartRow(), maze->getStartCol()));

    while( ! q.empty() )
    {
        std::pair<int, int> v = q.front();
        q.pop();
        numExplored++;

        r = v.first;
        c = v.second;

        /* This one if statement is different from the pseudo-code provided
           in lecture, because we want to stop when we've reached the goal.
           The code provided in lecture was for if you wanted to do a BFS
           that explored the entire graph.
        */
        if( r == maze->getGoalRow() && c == maze->getGoalCol() )
        {
            std::vector<Direction> path;
            std::stack<Direction> st;
            while( r != maze->getStartRow() || c != maze->getStartCol())
            {
                st.push( parent[ squareNumber(r,c) ]);
                switch( st.top() )
                {
                case UP: r++; break; // yes, r++.  I went up to get here...
                case DOWN: r--; break;
                case LEFT: c++; break;
                case RIGHT: c--; break;
                }
            }
            while ( ! st.empty() )
            {
                path.push_back(st.top());
                st.pop();
            }
            display->reportSolution(path, vt, numExplored);
            return;
        }

        /*
         * Now we're back to code that looks like the pseudo-code you've seen.
         * The difference here is that we aren't keeping track of distances;
           that's similar to the difference above.  You could add, and ignore,
           the vector that would result if you wanted to do so.
         */
        if ( maze->canTravel(UP, r, c) && ! vt.isVisited(r-1,c))
        {
            parent[squareNumber(r-1, c)] = UP;
            vt.setVisited(r-1,c);
            q.push(std::pair<int,int>(r-1, c));
        }
        // Note:  this is NOT "else if" ...
        if ( maze->canTravel(DOWN, r, c) && ! vt.isVisited(r+1,c) )
        {
            parent[squareNumber(r+1, c)] = DOWN;
            vt.setVisited(r+1, c);
            q.push(std::pair<int,int>(r+1, c));
        }
        if ( maze->canTravel(LEFT, r, c) && ! vt.isVisited(r,c-1) )
        {
            parent[squareNumber(r, c-1)] = LEFT;
            vt.setVisited(r, c-1);
            q.push(std::pair<int,int>(r, c-1));
        }
        if ( maze->canTravel(RIGHT, r, c) && ! vt.isVisited(r, c+1) )
        {
            parent[squareNumber(r, c+1)] = RIGHT;
            vt.setVisited(r, c+1);
            q.push(std::pair<int,int>(r, c+1));
        }
    }
}


int MazeSolver::squareNumber(int r, int c) const
{
    return maze->numCols() * r + c;
}


