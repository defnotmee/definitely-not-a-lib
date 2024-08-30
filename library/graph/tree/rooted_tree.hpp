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
#include"../../utility/template.cpp"
#endif

struct Tree{
    int n, root;
    vector<int> tin, tout, sub, pai, height;
    vector<bstring<int>> g;
    int m = 0;

    Tree(int n = 0, int root = 0) : n(n), root(root), 
    tin(n), tout(n), sub(n,1), pai(n,root), height(n), g(n){}

    // Takes a tree, changes the root and preprocesses it
    Tree(Tree& t, int root) : Tree(t.n, root){
        g = t.g;
        calc_tree();
    }

    void add_edge(int a, int b){
        g[a].push_back(b);
        g[b].push_back(a);
        m++;
    }

    void calc_tree(){
        assert(m == n-1);
        prec(root);
    }

    // call only after calc_tree
    pii find_centroids(){
        int id = root;

        while(true){
            for(int v : g[id]){
                if(pai[id] != v && sub[v]*2 >= n){
                    id = v;
                    goto NEXT;
                }
            }
            break;
            NEXT:;
        }
        if(sub[id]*2 == n)
            return {pai[id], id};
        return {id,id};
    }

    protected:
    void prec(int id){
        tout[id] = tin[id];
        for(int v : g[id]){
            if(v == pai[id])
                continue;
            pai[v] = id;
            height[v] = height[id]+1;
            tin[v] = tout[id]+1;
            prec(v);
            tout[id] = tout[v];
            sub[id]+=sub[v];
        }
    }
};
