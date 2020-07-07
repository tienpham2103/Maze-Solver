#include "MazeEdge.h"

MazeEdge::MazeEdge(int a, int b){
    x = a;
    y = b;
}

MazeEdge& MazeEdge::operator=(const MazeEdge& n){
    x = n.x;
    y = n.y;
    return *this;
}

bool MazeEdge::operator==(const MazeEdge& n) const{
    return x == n.x && y == n.y;
}

bool MazeEdge::operator!=(const MazeEdge& n) const{
    return x != n.x && y != n.y;
}

bool MazeEdge::operator<(const MazeEdge& n) const{
    if (x == n.x)
        return y < n.y;
    return x < n.x;
}

bool MazeEdge::operator>(const MazeEdge& n) const{
    if (x == n.x)
        return y > n.y;
    return x > n.x;
}

bool MazeEdge::operator<=(const MazeEdge& n) const{
    if (x == n.x)
        return y <= n.y;
    return x <= n.x;
}

bool MazeEdge::operator>=(const MazeEdge& n) const{
    if (x == n.x)
        return y >= n.y;
    return x >= n.x;
}
