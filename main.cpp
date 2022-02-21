///Kenny R. - Maze Program - Ms. Cullum
//This program reads in a maze from a text file and finds the path from start to goal
/*
Errors and Bugs:
There may be an error in the path finding if it is given a maze with converging paths

Big error: you cannot change the name of or delete maze.txt from the program folder. If you rename the current maze.txt file and place
a new maze.txt file, it will not work. The only thing you can do is copy one text file's contents into the text file one in the program folder.
I am not sure why this is, but it does not trip the "maze.txt not found" error in the fileSteal function.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include "Maze.h"
#include <cstdlib>

using namespace std;



int main()
{
    //Creates the maze 1 object from the Maze class
    Maze maze1;

    //This function gets the maze and the dimensions of the maze
    maze1.fileSteal();



    //This function figures out the path to the goal
    maze1.RecursiveMazePathDFS();

    //This function prints out the maze
    maze1.printMaze();

    maze1.printMazeAllegro();

    return 0;
}
