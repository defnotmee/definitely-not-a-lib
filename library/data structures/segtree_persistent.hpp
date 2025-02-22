/*
from https://github.com/defnotmee/definitely-not-a-lib

Persistent Segment Tree with point updates. By default, does point set and range sum

To create a segtree use PSegTree<type>(min_coord, max_coord).
You can effectively copy a segtree in O(1) by just copying a PSegTree instance.
*/

#ifndef O_O
#include"../utility/template.cpp"
#endif


// Bump allocator for extra performance:

// static char buf[450 << 20]; // by default can store 4.7e8 bytes
// void* operator new(size_t s) {
// 	static size_t i = sizeof buf;
// 	assert(s < i);
// 	return (void*)&buf[i -= s];
// }
// void operator delete(void*) {}

// implementation above from https://github.com/kth-competitive-programming/kactl/blob/main/content/various/BumpAllocator.h


// Uncomment if you need a custom struct.
// struct seg{
 
// };

template<typename seg = ll>
struct Node{
    Node(seg x = null) : x(x){}

    // identity value of element through merge operation
    static inline seg null = seg(); 

    seg x = null;
    Node* e = nullptr, *d = nullptr;

    static seg merge(seg a, seg b){
        return a+b;
    }

    void refresh(){
        if(!e)
            e = new Node(), d = new Node();
    }

    void update(ll l, ll r, ll q, seg val){
        if(l == r){
            x = val;
            return;
        }     
        
        refresh();

        ll m = (l+r)>>1;

        if(q <= m)
            (e = new Node(*e))->update(l,m,q,val);
        else (d = new Node(*d))->update(m+1,r,q,val);

        x = merge(e->x, d->x);
    }

    seg query(ll l, ll r, ll ql, ll qr){
        

        if(ql <= l && r <= qr){
            return x;
        }
        if(ql > r || l > qr)
            return null;
        
        refresh();

        ll m = (l+r)>>1;
        return merge(e->query(l,m,ql,qr), d->query(m+1,r,ql,qr));
    }

};

template<typename seg = ll>
struct PSegTree{
    
    ll l, r;
    Node<seg>* head;

    PSegTree(ll l, ll r) : l(l), r(r), head(new Node<seg>()){}

    seg query(ll ql, ll qr){
        return head->query(l,r,ql,qr);
    }

    void update(ll q, seg val){
        (head = new Node<seg>(*head))->update(l,r,q,val);
    }
};