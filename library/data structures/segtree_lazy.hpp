/*
from https://github.com/defnotmee/definitely-not-a-lib

Segment tree that allows range updates and queries. By default, it supports affine transformation
updates and sum queries, but commonly editted parts will be commented.

If a lazy segtree is not needed I recommend going for an segtree_iterative.hpp for
speed.

0-indexed by default.

=============================================================================

Declaration: SegTree<type>(size), where type is the datatype that represents a node of the segtree
Update: update(l, r, {mult, add}), for l <= i <= r, v[i] = v[i]*mult+add
Query: query(l,r), returns seg object equivalent to the sum of all values on range [l,r]

*/

#ifndef O_O
#include"../utility/template.cpp"
#endif

// Uncomment if you need a custom struct
// struct seg{
//     int x = 0; // identity value of the merge operation
// }

struct SegTree{
    using seg = ll; // <--- comment this if you need a custom struct


    struct lazy{
        ll mult = 1, add = 0; // "identity value" of lazy tag

        // Here is where you edit how to propagate the lazy tag for the children
        // of a segtree node
        void operator+=(const lazy& a){
            add*=a.mult;
            mult*=a.mult;
            add+=a.add;
        }
    };
    static inline seg null = seg(); // identity element through the merge operation

    // Here is where you change how to merge nodes
    static seg merge(seg a, seg b){
        return a+b;
    }

    vector<seg> tree;
    vector<lazy> lz;

    int sz, ql, qr;
    lazy val;

    SegTree(int n = 0){
        sz = n;
        tree = vector<seg>(4*n,null);
        lz = vector<lazy>(4*n);
    }
    
    void build(int id, int l, int r, vector<seg> & v){
        if(l == r){
            tree[id] = v[l];
            return;
        }

        const int e = id*2+1, d = id*2+2, m = (l+r)>>1;

        build(e,l,m,v);
        build(d,m+1,r,v);
        tree[id] = merge(tree[e],tree[d]);

    }

    SegTree(vector<seg> v){ // O(n) builder
        *this = SegTree(v.size());
        build(0,0,sz-1,v);
    }

    void refresh(int id, int l, int r){
        if(l != r){
            const int e = id*2+1, d = id*2+2, m = (l+r)>>1;

            lz[e]+=lz[id];
            lz[d]+=lz[id];
        }

        // Here is where you update the value of the current node based on the lazy tag
        tree[id] = tree[id]*lz[id].mult+lz[id].add*(r-l+1);
        lz[id] = lazy();
    }

    void update(int l, int r, lazy x){
        ql = l, qr = r, val = x;
        upd(0,0,sz-1);
    }

    seg query(int l, int r){
        ql = l, qr = r;
        return qry(0,0,sz-1);
    }

    private:
    
    void upd(int id, int l, int r){
        refresh(id,l,r);

        if(ql <= l && r <= qr){
            lz[id] += val;
            refresh(id,l,r);
            return;
        }
        if(ql > r || l > qr)
            return;

        const int e = id*2+1, d = id*2+2, m = (l+r)>>1;

        upd(e,l,m);
        upd(d,m+1,r);

        tree[id] = merge(tree[e], tree[d]);
    }

    seg qry(int id, int l, int r){
        refresh(id,l,r);

        if(ql <= l && r <= qr)
            return tree[id];
        
        if(ql > r || l > qr)
            return null;
        
        const int e = id*2+1, d = id*2+2, m = (l+r)>>1;
        return merge(qry(e,l,m), qry(d,m+1,r));
    }
};