/*
from https://github.com/defnotmee/definitely-not-a-lib

Stores a rooted tree with relevant information like height,
dfs order (tin and tout), height, the parent (pai) the size of the 
subtrees (sub). 

Intended to be inherited or composed for other algos.

Usage:

Tree(n,root): prepares tree of size n with vertices from 0 to n-1

add_edge(a,b): adds edge between a and b

After adding all edges, call calc_tree().
*/

#ifndef O_O
#include"template.cpp"
#endif

struct Tree{
    int n, root;
    vector<int> tin, tout, sub, pai, height;
    vector<bstring<int>> g;
    int m = 0;

    Tree(int n = 0, int root = 0) : n(n), root(root), 
    tin(n), tout(n), sub(n,1), pai(n,root), height(n), g(n){}

    // Takes a tree and changes the root
    Tree(Tree& t, int _root) {
        *this = t;
        root = _root;
        calc_tree();
    }

    void add_edge(int a, int b){
        g[a].push_back(b);
        g[b].push_back(a);
        m++;
        assert(m < n);
    }

    void calc_tree(){
        assert(m == n-1);
        prec(root);
    }

    // call only after calc_tree
    pii find_centroids(){
        int v = root;

        while(true){
            for(int u : g[v]){
                if(sub[u] <= n/2){
                    v = u;
                    goto NEXT;
                }
            }
            break;
            NEXT:;
        }

        if(sub[v]*2 == n)
            return {pai[v], v};
        return {v,v};
    }

    protected:
    int timer = -1;
    void prec(int id){
        tin[id] = ++timer;
        for(int v : g[id]){
            if(v == pai[id])
                continue;
            pai[v] = id;
            height[v] = height[id]+1;
            prec(v);
            sub[id]+=sub[v];
        }
        tout[id] = timer;
    }
};
