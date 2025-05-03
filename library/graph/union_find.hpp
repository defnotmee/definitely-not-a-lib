/*
from https://github.com/defnotmee/definitely-not-a-lib

Disjoint Set Union with union by size and path compression. Complexity is O(n*inverse_ackermann(n)), where n is the number of updates.

Use the "size" and "pai" functions to get the size of the group and the parent of the current vertex.
*/

#ifndef O_O
#include"../utility/template.cpp"
#endif


class UnionFind{
    vector<int> v; // Either parent (if v[i] >= 0) or size (if v[i] < 0 and i is a root) of the component

    public:
    UnionFind(int n = 0) : v(n,-1){}

    int find(int id){
        return v[id] < 0 ? id : find(v[id]);
    }

    int size(int id){ // Returns size of the component id belongs to
        return -v[find(id)];
    }

    int pai(int id){ // Returns parent of id
        return v[id] < 0 ? id : v[id];
    }

    // Returns 1 if a and b were in different groups.
    // Useful for Kruskal.
    bool onion(int a, int b){
        a = find(a);
        b = find(b);

        if(a == b)
            return 0;

        if(size(a) > size(b)) // union by size
            swap(a,b);

        v[b] += v[a];
        v[a] = b;
        return 1;
    }

    bool same(int a, int b){
        return find(a) == find(b);
    }
};
