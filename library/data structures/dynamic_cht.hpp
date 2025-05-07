/**
 * from https://github.com/defnotmee/definitely-not-a-lib
 * 
 * Implements a data structure where you can insert functions of the form
 * f(x) = ax+b and query the maxmimum/minimum value of f(x)
 * 
 * Usage: declare CHT<1> if you want to find maximum f(x) queries, and
 * CHT<-1> if you want minimum f(x) queries.
 * 
 */
#ifndef O_O
#include"../utility/template.cpp"
#endif

using line = array<ll,2>;

// mult = 1 for maximum, mult = -1 for minimum
template<ll mult = 1>
struct CHT{
    struct poss{
        line l;
        mutable ll minx;
        
        bool operator<(ll x) const {
            return minx < x;
        }
        bool operator<(poss o) const {
            return l < o.l;
        }
    };

    // if x can be double, change this to -INFINITY
    const ll inf = LLONG_MAX;

    // if x can be double, change this to a/b
    ll div_ceil(ll a, ll b){
        return a/b+(a%b!=0 && (a^b)>0);
    }    

    multiset<poss,less<>> s;
    // assuming l1 <= l2, finds smallest x such that l1(x) <= l2(x)
    ll intersect(line l1, line l2){
        ll da = l2[0]-l1[0], db = l1[1]-l2[1];
        if(da == 0)
            return -inf;
        // cerr << div_ceil(db,da) << '\n';
        return div_ceil(db,da);
    }

    // Inserts f(x) = ax*b in the structure
    void insert(ll a, ll b){
        line l = {a*mult,b*mult};
        auto it = s.lower_bound({l,0});
        ll nxtin = it == s.end() ? inf : intersect(l,it->l);
        if(nxtin < it->minx)
            return;
        it->minx = nxtin;
        it = s.insert({l,-inf});
        while(it != s.begin()){
            auto prv = prev(it);
            ll in = intersect(prv->l, l);
            if(prv->minx < in){
                it->minx = in;
                break;
            }
            s.erase(prv);
        }
    }

    // Finds maximum f(x) in the structure if mult = 1 and minimum f(x) if mult = -1
    ll query(ll x){
        auto [a,b] = prev(s.lower_bound(x+1))->l;
        return mult*(a*x+b);
    }
};