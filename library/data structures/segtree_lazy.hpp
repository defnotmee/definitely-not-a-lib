// TODO: Make build accept elements of type seg like iterativesegtree.hpp

/*
from https://github.com/defnotmee/definitely-not-a-lib

Declaration: SegTree(size)
Update: update(l, r, {mult, add}), for l <= i <= r, v[i] = v[i]*mult+add
Query: query(l,r), returns seg object equivalent to the sum of all values on range [l,r]

=============================================================================

If a lazy segtree is not needed I recommend going for an iterativesegtree.hpp .
You can erase the parts where it does lazy propagation also.

Segtree for affine transformations and range sums in O(log(n)).
Made to be as customizable and copy-pasteable as possible, speed 
and code size is not a concern. 

0-indexed by default.

The parts you'll commonly edit will be commented.
*/

#ifndef O_O
#include"../utility/template.cpp"
#endif

struct SegTree{
    struct seg{
        ll x = 0; // "identity value" of the operation
    };

    struct lazy{
        ll mult = 1, add = 0; // "identity value" of lazy tag

        // only for C++20, get fucked (implement your own ==) otherwise
        auto operator<=>(const lazy& a) const = default;

        // Here is where you edit how to propagate the lazy tag for the children
        // of a segtree node
        void operator+=(const lazy& a){
            add*=a.mult;
            mult*=a.mult;
            add+=a.add;
        }
    };

    vector<seg> tree; // yes, this is all for the pun
    vector<lazy> lz;

    int sz, ql, qr;
    lazy val;

    // Here is where you change how to merge nodes
    inline seg merge(seg a, seg b){
        return {a.x+b.x};
    }

    SegTree(int n = 0){
        sz = n;
        tree = vector<seg>(4*n);
        lz = vector<lazy>(4*n);
    }
    
    
    // Comment the next two functions if you dont need a O(n) builder

    void build(int id, int l, int r, vector<ll> & v){
        if(l == r){
            tree[id].x = {v[l]};
            return;
        }

        const int e = id*2+1, d = id*2+2, m = (l+r)>>1;

        build(e,l,m,v);
        build(d,m+1,r,v);
        tree[id] = merge(tree[e],tree[d]);

    }

    SegTree(vector<ll> v){
        *this = SegTree(v.size());
        build(0,0,sz-1,v);
    }

    void refresh(int id, int l, int r){
        if(lz[id] == lazy())
            return;
        
        if(l != r){
            const int e = id*2+1, d = id*2+2, m = (l+r)>>1;

            lz[e]+=lz[id];
            lz[d]+=lz[id];
        }

        // Here is where you update the value of the current node based on the lazy tag
        tree[id] = {tree[id].x*lz[id].mult+lz[id].add*(r-l+1)};
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
            return seg();
        
        const int e = id*2+1, d = id*2+2, m = (l+r)>>1;
        return merge(qry(e,l,m), qry(d,m+1,r));
    }
};
