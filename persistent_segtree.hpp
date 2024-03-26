/*
from https://github.com/defnotmee/definitely-not-a-lib

Quite slow but at least it doesn't have memory leaks :D

To make a segtree use PSegTree<type>(min_coord, max_coord).
You can effectively copy a segtree in O(1) by just copying a PSegTree instance.
*/
 
#ifndef O_O
#include"template.cpp"
#endif
 
// Uncomment if you need a custom struct. Also construct a segtree using PSegTree<seg>
// struct seg{
 
// };
 
template<typename seg = ll>
struct SegNode {
    using sp = shared_ptr<SegNode<seg>>;
    #define make(...) make_shared<SegNode<seg>>(__VA_ARGS__)
 
    sp e = nullptr, d = nullptr;
    seg x = 0;
    
    SegNode(seg _x = 0) : x(_x){};
 
    SegNode(SegNode<seg>& b) : e(b.e), d(b.d), x(b.x){};

    static seg merge(seg e, seg d){
        return e+d; 
    }
    
    constexpr seg get(){
        return this ? x : seg();
    }

    void update(ll l, ll r, ll target, seg val){
        if(l == r){ 
            x = val;
            return;
        }

        if(!e)
            e = make(), d = make();

        ll m = (l+r)>>1;
 
        if(target <= m)
            (e = make(*e))->update(l,m,target,val);
        else (d = make(*d))->update(m+1,r,target,val);

        x = merge(e->get(), d->get());
    }
 
    seg query(ll l, ll r, ll ql, ll qr){
        if(ql <= l && r <= qr){
            return x;
        }
        if(ql > r || l > qr)
            return seg();
        
        if(!e)
            e = make(), d = make();
        
        ll m = (l+r)>>1;
        
        return merge(e->query(l,m,ql,qr),
            d->query(m+1,r,ql,qr));
 
    }
    
};
 
template<typename seg = ll>
struct PSegTree{
    shared_ptr<SegNode<seg>> head;
    ll l, r;
 
    PSegTree(ll _l, ll _r) : l(_l), r(_r), head(new SegNode<seg>){};
 
    void update(ll id, seg x){
        (head = make(*head))->update(l,r,id,x);
    }
 
    seg query(ll ql, ll qr){
        return head->query(l,r,ql,qr);
    }
};