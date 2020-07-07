#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <vector>
#include <set>
#include <queue>
#include "MazeEdge.h"
#include "Vertex.h"

using namespace std;

class Maze
{
public:
    Maze(int r, int c); //Build a maze of "row" rows and "col" columns
//    void printMaze(); //Print the maze;
    void solveMaze();
    void removeSomeEdges(int percentage); //Remove "percentage" % of edges from the maze
    void MainLoop(); //Main event loop for openGL

protected:

    struct propagation{
	int id;
	int value;
    };
    void HandleEventOnDisplay();
    void HandleEventOnMouseLeftButtonDown(const double mousePosX, const double mousePosY);
    bool HandleEventOnNormalKeyPress(const int key);
    static void CallbackEventOnDisplay();
    static void CallbackEventOnMouse(int button, int state, int x, int y);
    static void MousePosition(const int x, const int y, double *posX, double *posY);
    static void CallbackEventOnNormalKeyPress(unsigned char key, int x, int y);
    void DrawMaze();
    void DrawVertical(int v);
    void DrawHorizontal(int h);
    void DrawStart();
    void DrawFinish();
    void DrawSolution();
    void ColorClearance();
    void Propagate();
    bool isNearWall(int id);

    vector<propagation> propagationVector;
    int mouseClicked;
    float startX, startY;
    float finishX, finishY;

private:
    struct maps{
        int name;
        int parent;
        double totalCost;
        bool operator<(const maps &m) const
        {
            return totalCost < m.totalCost;
        }
    };

    int rows; //Number of rows in the grid
    int columns; //Number of columns in the grid
    int totalVertices; //Total vertices = rows * columns
    vector<MazeEdge> grid; //The set of all edges
    vector<MazeEdge> maze; //The subset of chosen edges
    vector<Vertex> vertexList; //Set of all vertices
    vector<vector<int> > adjMat; //The adjacency matrix
    //Stack myStack; //The stack to solve the maze using DFS
    vector<int> solutionVertexList; //List of Vertices in the solution of the maze
    double percentageEdgeRemove; //Percentage of edges being removed
    int edgeRemoved; //Number of edges being removed
    int totalEdges; //Total number of edges in the maze
    int start; //The start cell in the maze need to be solved
    int finish; //The finish cell in the maze need to be solved

    void fillGrid(); //Fill the grid vector with all possible edges
    void generateMaze(); //Fill the maze set with the chosen edges
//    void vertical(int v); //Print out the vertical edges of a given row of the maze
//    void horizontal(int h); //Print out the horizontal edges of a given row of the maze
//    void topbot(); //Print out the top/bottom line of the maze
    void addVertex(); //Add the vertices to the vertex list
    void addGraphEdge(); //Add all the graph edges to the adjacency matrix
    void removeGraphEdge(); //Remove the graph edges that are the maze edges
    //void solveMazeDFS(); //Solve the maze from "start" cell to "finish" cell
    //int getAdjUnvisitedVertexIndex(int v); //Return the adjacency unvisited vertex of vertex "v"

    //A* method
    set<int> closedSet;
    set<int> openSet;
    int xSta, ySta; //Coordinate of the start node
    int xFin, yFin; //Coordinate of the finish node
    vector<int> totalPath;
    void solveMazeAStar();
    double EdgeWeight(int current, int neighbor);
    double heuristicCostEstimate(int startNode);
    void reconstructPath(int cameFrom[], int current);

    //Car
    void CarInitialization();
    enum
	{
		STATE_X,
		STATE_Y,
		STATE_THETA
	};
    double carDimX;
    double carDimY;
    double carState[3];
    double STATE_MOVE_X;
    double STATE_MOVE_Y;
    double STATE_MOVE_THETA;
};

#endif // MAZE_H_INCLUDED
