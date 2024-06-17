

/*
from https://github.com/defnotmee/definitely-not-a-lib

Disjoint Set Union with union by rank and path compression. O((n+m)inverse_ackermann).
*/

#ifndef O_O
#include"template.cpp"
#endif


struct UnionFind{
    vector<int> sz; // Either parent (if v[i] <= 0) or size (if v[i] > 0 and i is a root) of the component

    UnionFind(int n = 0) : sz(n,1){}

    int find(int id){
        if(sz[id] > 0)
            return id;
        return sz[id] = -find(-sz[id]);
    }

    // Returns 1 if a and b were in different groups.
    // Useful for Kruskal.
    bool onion(int a, int b){
        a = find(a);
        b = find(b);

        if(a == b)
            return 0;

        if(sz[a] > sz[b])
            swap(a,b);

        sz[b] += sz[a];
        sz[a] = -b;
        return 1;
    }

    bool same(int a, int b){
        return find(a) == find(b);
    }

    int pai(int id){ // Returns parent of id
        return sz[id] < 0 ? -sz[id] : id;
    }
};
