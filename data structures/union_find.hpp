

/*
from https://github.com/defnotmee/definitely-not-a-lib

why am i doing this
*/

#ifndef O_O
#include"template.cpp"
#endif


struct UnionFind{
    vector<int> pai;

    UnionFind(int n = 0){
        pai = vector<int>(n);
        iota(all(pai),0);
    }

    int find(int id){
        if(pai[id] == id)
            return id;
        return pai[id] = find(pai[id]);
    }

    // Returns 1 if a and b were in different groups.
    // Useful for Kruskal.
    bool onion(int a, int b){
        a = find(a);
        b = find(b);

        if(a == b)
            return 0;

        // Here is where you edit how to merge nodes
        pai[a] = b;
        
        return 1;
    }

    bool same(int a, int b){
        return find(a) == find(b);
    }
};
