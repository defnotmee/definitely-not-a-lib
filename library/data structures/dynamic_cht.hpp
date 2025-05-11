/**
 * from https://github.com/defnotmee/definitely-not-a-lib
 * 
 * based on https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h
 * 
 * Implements a data structure where you can insert functions of the form
 * f(x) = ax+b and query the maxmimum/minimum value of f(x)
 * 
 * Usage: declare CHT<1> if you want to find maximum f(x) queries, and
 * CHT<-1> if you want minimum f(x) queries.
 * 
 * O(log(n)) amortized insertion and O(log(n)) queries
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
        mutable ll maxx;
        
        bool operator<(ll x) const {
            return maxx < x;
        }
        bool operator<(poss o) const {
            return l < o.l;
        }
    };

    // if x can be double, change this to -INFINITY
    static const ll inf = LLONG_MAX;

    // if x can be double, change this to a/b
    ll div_floor(ll a, ll b){
        return a/b-(a%b!=0 && (a^b)<0);
    }

    multiset<poss,less<>> s;
    // assuming l1 <= l2, finds smallest x such that l1(x) <= l2(x)
    ll intersect(line l1, line l2){
        ll da = l2[0]-l1[0], db = l1[1]-l2[1];
        if(da == 0)
            return -inf;
        return div_floor(db,da);
    }

    public:
    // Inserts f(x) = ax*b in the structure
    void insert(ll a, ll b){
        line l = {a*mult,b*mult};
        
        auto it = next(s.insert({l}));
        while(it != s.end() && intersect(l,it->l) >= it->maxx)
            it = s.erase(it);
        prev(it)->maxx = it == s.end() ? inf : intersect(l,it->l);
        it--;

        if(it!=s.begin()){
            auto prv = prev(it);
            ll in = intersect(prv->l, l);
            if(in > it->maxx){
                s.erase(it);
                return;
            }
            prv->maxx = in;
            while(prv != s.begin() && prev(prv)->maxx >= prv->maxx){
                s.erase(prv);
                prv = prev(it);
                prv->maxx = intersect(prv->l,l);
            }
        }
    }

    // Finds maximum f(x) in the structure if mult = 1 and minimum f(x) if mult = -1
    ll query(ll x){
        auto [a,b] = s.lower_bound(x)->l;
        return mult*(a*x+b);
    }
};