/*
from https://github.com/defnotmee/definitely-not-a-lib

Extension of tree_rooted.hpp that calculates lca in
O(nlogn) precomputation and O(1) per query.

Isnt able to calculate things on the path to the LCA.
(see binlift.hpp for that)
*/

#ifndef O_O
#include"template.cpp"
#include"rooted_tree.hpp"
#endif

struct LCATree : Tree {
    vector<int> euler, eid;
    matrix<int> sparse;
    
    LCATree(int n = 0, int root = 0) : Tree(n, root), eid(n) {
        euler.reserve(2*n);
    }

    int get_lower(int a, int b){
        return height[a] < height[b] ? a : b;
    }

    void calc_tree(){
        assert(m == n-1);
        prec(root);

        // not on rooted_tree.hpp
        int lg = log2(euler.size())+1;
        sparse = matrix<int>(lg, euler);
        for(int i = 1; i < lg; i++){
            for(int j = 0; j + (1<<i) <= euler.size(); j++)
                sparse[i][j] = get_lower(sparse[i-1][j], sparse[i-1][j+(1<<i-1)]);
        }
    }

    int lca(int a, int b){
        a = eid[a], b = eid[b];
        if(a > b)
            swap(a,b);
        int logg = log2(b-a+1);
        return get_lower(sparse[logg][a], sparse[logg][b-(1<<logg)+1]);
    }

    int dist(int a, int b){
        return height[a]+height[b]-2*height[lca(a,b)];
    }

    private:

    void prec(int id){
        tout[id] = tin[id];
        eid[id] = euler.size(); // not on rooted_tree.hpp
        euler.push_back(id); // not on rooted_tree.hpp
        for(int v : g[id]){
            if(v == pai[id])
                continue;
            pai[v] = id;
            height[v] = height[id]+1;
            tin[v] = tout[id]+1;
            prec(v);
            tout[id] = tout[v];
            sub[id]+=sub[v];
            euler.push_back(id); // not on rooted_tree.hpp
        }
    }
};