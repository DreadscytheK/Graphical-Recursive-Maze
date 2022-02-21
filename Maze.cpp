///Kenny R. - Maze Program - Ms. Cullum
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "Maze.h"

using namespace std;

///Function prints out the maze to the commandline
void Maze::printMaze()
{
    //For statement loops through the maze and prints out each character
    for (int i=0; i<mRow; i++) {
        for (int j=0; j<mCol; j++) {
            if(maze[i][j]=='-') {
                maze[i][j]='.';
            }
            cout << maze[i][j];
        }
        cout << endl;
    }
}

///Function finds the path from the start to the goal
int Maze::RecursiveMazePathDFS()
{
    //Every if statement here checks if the character '.' or 'G' is in the space it is looking at. Each if statement
    //is looking in a different direction, and if an if statement meets it conditions, it then checks if the spot is
    //'G' and if it is then it exits the function, if it is not then it changes the character of the spot it is going to
    //to '+' and then returns itself with the coordinates changed based on the direction.

    //Goes East
    if(maze[x][y+1]=='.'||maze[x][y+1]=='G') {
        //Checks if G is the character in the specified direction
        if(x==gx&&y+1==gy) {
            return 0;
        }
        //Changes the character in the specified direction to '+'
        maze[x][y+1]='+';
        //Returns RecursiveMazePathDFS with all the needed variables, except it changes the x and y variables
        //Based on the specified direction
        y++;
        return RecursiveMazePathDFS();
    }
    //Goes West
    else if(maze[x][y-1]=='.'||maze[x][y-1]=='G') {
        //Checks if G is the character in the specified direction
        if(x==gx&&y-1==gy) {
            return 0;
        }
        //Changes the character in the specified direction to '+'
        maze[x][y-1]='+';
        //Returns RecursiveMazePathDFS with all the needed variables, except it changes the x and y variables
        //Based on the specified direction
        y--;
        return RecursiveMazePathDFS();
    }
    //Goes South
    else if(maze[x+1][y]=='.'||maze[x+1][y]=='G') {
        //Checks if G is the character in the specified direction
        if(x+1==gx&&y==gy) {
            return 0;
        }
        //Changes the character in the specified direction to '+'
        maze[x+1][y]='+';
        //Returns RecursiveMazePathDFS with all the needed variables, except it changes the x and y variables
        //Based on the specified direction
        x++;
        return RecursiveMazePathDFS();
    }
    //Goes North
    else if(maze[x-1][y]=='.'||maze[x-1][y]=='G') {
        //Checks if G is the character in the specified direction
        if(x-1==gx&&y==gy) {
            return 0;
        }
        //Changes the character in the specified direction to '+'
        maze[x-1][y]='+';
        //Returns RecursiveMazePathDFS with all the needed variables, except it changes the x and y variables
        //Based on the specified direction
        x--;
        return RecursiveMazePathDFS();
    }

    //These if statements only work if there is no new direction. They activate depending on if there is a
    //'+' character in any of the specified directions. They then put a '-' character where they are going
    //and then run the RecursiveMazePathDFS function in the direction they are going. This is how the function
    //backtracks.

    //Goes West
    if(maze[x][y-1]=='+') {
        //Changes the character in the specified direction to '-'
        maze[x][y]='-';
        //Returns RecursiveMazePathDFS with all the needed variables, except it changes the x and y variables
        //Based on the specified direction
        y--;
        return RecursiveMazePathDFS();
    }
    //Goes South
    else if(maze[x+1][y]=='+') {
        //Changes the character in the specified direction to '-'
        maze[x][y]='-';
        //Returns RecursiveMazePathDFS with all the needed variables, except it changes the x and y variables
        //Based on the specified direction
        x++;
        return RecursiveMazePathDFS();
    }
    //Goes East
    else if(maze[x][y+1]=='+') {
        //Changes the character in the specified direction to '-'
        maze[x][y]='-';
        //Returns RecursiveMazePathDFS with all the needed variables, except it changes the x and y variables
        //Based on the specified direction
        y++;
        return RecursiveMazePathDFS();
    }
    //Goes North
    else if(maze[x-1][y]=='+') {
        //Changes the character in the specified direction to '-'
        maze[x][y]='-';
        //Returns RecursiveMazePathDFS with all the needed variables, except it changes the x and y variables
        //Based on the specified direction
        x--;
        return RecursiveMazePathDFS();
    }
}

///File steal function gets the maze and its dimensions
int Maze::fileSteal()
{
    //Declaring variables
    string row;
    mRow = 0;
    mCol = 0;

    //Gets the text file and gives an error if it does not open
    ifstream fin("maze.txt");
    if (!fin.is_open()) {
        cout << "maze.txt not found" << endl;
        return 1;
    }

    //Find out the size
    while (!fin.eof()) {
        fin >> row;
        mRow++;
    }
    mCol = row.length();

    //Go to beginning of file
    fin.clear(); //Clear bad state after eof
    fin.seekg( 0 );

    //Resize maze
    maze.resize(mRow);
    for (int i=0; i<mRow; i++)
        maze[i].resize(mCol);

    //Read maze (add finding S and G)
    for (int i=0; i<mRow; i++) {
        for (int j=0; j<mCol; j++) {
            fin >> maze[i][j];
            if(maze[i][j]=='S') {
                y = i;
                x = j;
            }
            if(maze[i][j]=='G') {
                gx = i;
                gy = j;
            }
        }
    }
    fin.close();

    return 0;
}

///Prints the maze with allegro
void Maze::printMazeAllegro()
{
    //Declaring variables
    int width = mCol*50;
    int height = (mRow-1)*50;

    //Initializes libraries that are used
    al_init();
    al_init_image_addon();
    al_init_primitives_addon();

    //Creates display
    ALLEGRO_DISPLAY *display1 = nullptr;
    display1 = al_create_display(width, height);
    al_clear_to_color(al_map_rgb(10,115,229));

    //Two for statements run through the maze and depending on the character it will print a differently coloured square
    for (int j=0; j<mRow; j++) {
        for (int i=0; i<mCol; i++) {
            if(maze[j][i]=='S') {
                al_draw_filled_rectangle(j*50,j*50,i*50+50,j*50+50, al_map_rgb(45,221,33));
            }
            else if(maze[j][i]=='#') {
                al_draw_filled_rectangle(i*50,j*50,i*50+50,j*50+50, al_map_rgb(207,87,35));
            }
            else if(maze[j][i]=='G') {
                al_draw_filled_rectangle(i*50,j*50,i*50+50,j*50+50, al_map_rgb(236,176,2));
            }
            else if(maze[j][i]=='+') {
                al_draw_filled_rectangle(i*50,j*50,i*50+50,j*50+50, al_map_rgb(41,47,128));
            }

        }
    }

    //Sends the allegro to the window
    al_flip_display();

    //Rests then destroys the display
    al_rest(20);
    al_destroy_display(display1);
}
