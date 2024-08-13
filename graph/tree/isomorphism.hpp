/*
from https://github.com/defnotmee/definitely-not-a-lib

Gives a way to hash a tree, either considering it rooted or not.
(choose the corresponding struct depending on the case)

Usage:

Rooted_Isomorphism(n, root) initializes the structure for a
tree of size n (0 indexed) rooted at root.

add_edge(a,b) is self explanatory

After adding all edges, call calc_tree() to get the hash of the tree.

After calling calc_tree(), hashsub[i] will contain the hash of subtree i.

For Unrooted_Isomorphism, the biggest difference is that the hashub array will
be meaningless.
*/

#ifndef O_O
#include"template.cpp"
#include"rooted_tree.hpp"
#endif

struct Rooted_Isomorphism : Tree{

    ull seed;
    vector<ll> hashsub;

    ull hasher(ull x){
        // http://xorshift.di.unimi.it/splitmix64.c
        x+=0x9e3779b97f4a7c15;
        x = (x^(x>>30)) * 0xbf58476d1ce4e5b9;
        x = (x^(x>>27)) * 0x94d049bb133111eb;
        return x^(x>>31)^seed;
    }

    Rooted_Isomorphism(int n = 0, int root = 0, ull seed = RANDOM) : Tree(n,root), seed(seed), hashsub(n) {}

    // use this if you want the same graph for a different root, otherwise important info wont be reset
    Rooted_Isomorphism(Rooted_Isomorphism& r, int root) : Rooted_Isomorphism(r.n, root){
        m = r.m;
        g = r.g;
    }

    // returns hash of the whole tree
    ull calc_tree(){
        assert(m == n-1);
        prec(root);
        return hashsub[root];
    }

    private:

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
            hashsub[id]+=hashsub[v]; // not on rooted_tree.hpp
        }
        hashsub[id] = hasher(hashsub[id]); // not on rooted_tree.hpp
    }

};

struct Unrooted_Isomorphism{
    Rooted_Isomorphism tree;

    Unrooted_Isomorphism(int n) : tree(n){}

    void add_edge(int a, int b){
        tree.add_edge(a,b);
    }

    ull calc_tree(){
        tree.calc_tree();
        auto [c1, c2] = tree.find_centroids();
        
        tree = Rooted_Isomorphism(tree,c1);
        ull tmp = tree.calc_tree();

        tree = Rooted_Isomorphism(tree,c2);

        return min(tmp, tree.calc_tree());
    }
};