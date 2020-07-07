#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED

class Vertex
{
public:
    Vertex(int n); //Create a vertex with the name "n"
    int getName(); //Get the name of the vertex
    void setHeuristic(int rows, int columns, int xFin, int yFin);
    double getHeuristic();
    bool isVisited; //Check if the vertex is visited
private:
    int name; //Name of the vertex
    double heuristic;
    double cost;

};

#endif // VERTEX_H_INCLUDED
