#include "DisjointSet.h"

DisjointSet::DisjointSet(int n){
    roze = new int[n+1];
    nos = n;
    for (int i = 1; i<n+1; i++)
    {
        roze[i] = -1; //Initially, each one-element set is the root and the size is 1
    }
}

int DisjointSet::numSets(){
    return nos;
}

int DisjointSet::Find(int i){
    while (roze[i] > 0) //While i is not the root of the subset (Because the roze[root] stores the size of the subset, which is a negative number)
    {
        i = roze[i];
    }
    return i;
}

void DisjointSet::Union(int root1, int root2){
    nos--;
    if (roze[root1] < roze[root2]) //If size of subset root1 > size of subset root2 (because size is stored in negative number)
    {
        roze[root1] += roze[root2]; //Adjust the size
        roze[root2] = root1; //Do the union
    }
    else {
        roze[root2] += roze[root1];
        roze[root1] = root2;
    }
}
