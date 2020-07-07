#include "Vertex.h"
#include <cmath>
#include <stdlib.h>

Vertex::Vertex(int n){
    name = n;
    isVisited = false;
    heuristic = 0;
}

int Vertex::getName(){
    return name;
}

void Vertex::setHeuristic(int rows, int columns, int xFin, int yFin){
    int x, y;
    div_t divResult;
    divResult = div(name, columns);
    if (divResult.rem == 0)
        x = columns;
    else x = divResult.rem;

    divResult = div(name, rows);
    if (divResult.rem == 0)
        y = rows;
    else y = divResult.rem;
    heuristic = sqrt(pow(abs(x - xFin), 2) + pow(abs(y - yFin), 2));
}

double Vertex::getHeuristic(){
    return heuristic;
}
