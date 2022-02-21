///Kenny R. - Maze Program - Ms. Cullum
#include <iostream>

using namespace std;

class Maze{
public:

    //Function gets the maze from a text file
    int fileSteal();

    //Function figures out the path from start to goal
    int RecursiveMazePathDFS();

    //Prints the maze to the commandline
    void printMaze();

    //Prints the maze with allegro
    void printMazeAllegro();

private:
    vector<vector <char> > maze;
    int mRow;
    int mCol;
    int x;
    int y;
    int gx;
    int gy;
};
