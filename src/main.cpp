#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Maze.h"

using namespace std;

int main()
{
    srand(time(NULL));

    int rows, columns;
    int percentage;

    //Reading input from the user
    cout << "Number of rows: ";
    cin >> rows;
    cout << "Number of columns: ";
    cin >> columns;

    Maze maze(rows,columns); //Create and generate a maze
    //maze.MainLoop();
    //maze.printMaze(); //Print the maze
    maze.solveMaze();
    //maze.solveMaze(1, rows*columns); //Find the path from cell 3 to cell 25
                                   //You can change "3" and "25" to different numbers to find a different path.
                                   //For example: maze.solveAndPrintMaze(1, rows*columns) to find the path
                                   //from entrance to exit.

    /*cout << endl << "Percentage of edges remove: "; //input is integer only
    cin >> percentage;
    maze.removeSomeEdges(percentage);*/
    return 0;
}
