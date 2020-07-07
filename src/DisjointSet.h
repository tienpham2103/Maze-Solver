#ifndef DISJOINTSET_H_INCLUDED
#define DISJOINTSET_H_INCLUDED

class DisjointSet
{
public:
    DisjointSet(int n); //Build a disjoint set with n one-element sets
    int numSets(); //Return number of subsets
    int Find(int i); //Return the root of i
    void Union(int root1, int root2); //Union two roots

private:
    int *roze; //Array of ROot and its siZE (Size is stored as a negative number)
    int nos; //Number Of Subsets
};

#endif // DISJOINTSET_H_INCLUDED
