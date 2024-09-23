/*
from https://github.com/defnotmee/definitely-not-a-lib

Segtree that does point updates and range queries (by default, point set range sum). 
The merge operation can be non-commutative. 

Implementation based on https://codeforces.com/blog/entry/18051
Different from the implementation on that blog, the range on query is [l,r] instead of
[l,r)

Commonly changed parts will be commented.
*/

#ifndef O_O
#include"../utility/template.cpp"
#endif

// In case you want nodes to be a custom struct:

// uncomment this
// struct seg {
//     ll x = 0; // "identity value" of operation
// };

template<typename seg = ll> // comment this
struct SegPoint{

    int sz;
    vector<seg> tree;

    SegPoint(int n = 0): sz(n), tree(2*n){};

    SegPoint(vector<seg> v){ // O(n) builder
        *this = SegPoint(v.size());

        for(int i = 0; i < sz; i++)
            tree[i+sz] = v[i];
        for(int i = sz-1; i > 0; i--)
            tree[i] = merge(tree[2*i], tree[2*i+1]);
    }

    static seg merge(seg a, seg b){ 
        return {a+b}; // here is where 2 nodes are merged
    }
    void update(int id, seg val){
        id+=sz;

        tree[id] = val; // here is where you update a point

        id>>=1;

        while(id){
            tree[id] = merge(tree[2*id], tree[2*id+1]);
            id>>=1;
        }
    }

    seg query(int l, int r){
        l += sz;
        r += sz+1;
        
        seg retl = seg(), retr = seg();

        while(l < r){
            if(l&1)
                retl = merge(retl, tree[l++]);
            if(r&1)
                retr = merge(tree[--r], retr);

            l>>=1;
            r>>=1;
        }

        return merge(retl,retr);
    }

};