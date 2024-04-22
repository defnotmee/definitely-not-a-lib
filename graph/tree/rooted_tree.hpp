/*
from https://github.com/defnotmee/definitely-not-a-lib

Stores a rooted tree with relevant information like height,
dfs order (tin and tout), height, the parent (pai) the size of the 
subtrees (sub). Also erases edges to the parent so they
don't have to be checked later (and you can use pai[i]
to find it if you need it).

Intended to be inherited or composed for other algos.

Usage:

Tree(n,root): prepares tree of size n with vertices from 0 to n-1

add_edge(a,b): adds edge between a and b

After adding all edges, call calc_tree(). The information will be calculated
and edges pointing to the parent will have be erased.
*/

#ifndef O_O
#include"template.cpp"
#endif

struct Tree{
    int n, root;
    vector<int> tin, tout, sub, pai, height;
    vector<bstring<int>> g;
    int m = 0;

    Tree(int n = 0, int root = 0) : n(n), root(root), tin(n), tout(n), sub(n,1), pai(n,root), height(n), g(n){}

    void add_edge(int a, int b){
        g[a].push_back(b);
        g[b].push_back(a);
        m++;
        if(m == n){
            cerr << "Too many edges >:(" << endl;
            exit(1);
        }
    }

    void calc_tree(){
        if(m < n-1){
            cerr << "Too little edges >:(" << endl;
            exit(1);
        }
        prec(root);
    }

    protected:
    int timer = -1;
    // Erases back edges and calcs everything
    void prec(int id){
        tin[id] = ++timer;
        for(int i = 0; i < g[id].size(); i++){
            int& viz = g[id][i];
            if(viz == pai[id]){
                swap(viz,g[id].back());
                g[id].pop_back();
                i--;
                continue;
            }
            pai[viz] = id;
            height[viz] = height[id]+1;
            prec(viz);
            sub[id]+=sub[viz];
        }
        tout[id] = timer;
    }
};
