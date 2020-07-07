#ifndef MAZEEDGE_H_INCLUDED
#define MAZEEDGE_H_INCLUDED

class MazeEdge
{
public:
    MazeEdge(int a, int b); //Build an edge

    //Redefining the operators =, ==, !=, <, >, <=, >=
    //So that they can be used for Edge values
    //For example: after we define
    //Edge e1, e2
    //We can perform operations like:
    //e1 = e2
    //e1 == e2
    //e1 < e2
    MazeEdge& operator=(const MazeEdge& n);
    bool operator==(const MazeEdge& n) const;
    bool operator!=(const MazeEdge& n) const;
    bool operator<(const MazeEdge& n) const;
    bool operator>(const MazeEdge& n) const;
    bool operator<=(const MazeEdge& n) const;
    bool operator>=(const MazeEdge& n) const;

    //The coordination of the edge
    int x;
    int y;
};

#endif // MAZEEDGE_H_INCLUDED
