/*
from https://github.com/defnotmee/definitely-not-a-lib

Maintains a partially ordered set (or pareto front), that is,
a list of pairs (x[i], y[i]) such that if for i < j:
x[i] < x[j], then y[i] < y[j].

In a practical sense, "increasing x is bad but incresing y
is good". Maintaining this convention makes it more convenient.

Can only do insertions. O(logn) per insert.
*/

#ifndef O_O
#include"header.h"
#endif

struct pareto{
    struct item{
        ll x, y;

        bool operator<(item c) const {
            if(x == c.x)
                return y < c.y;
            return x < c.x;
        }
    };

    set<item> s;

    void insert(ll x, ll y){
        auto it = s.lower_bound({x,y});

        if(it != s.begin()){
            auto it2 = it;
            it2--;

            if(it2->y >= y)
                return;
        }

        while(it != s.end() && y >= it->y){
            it = s.erase(it);
        }

        s.insert({x, y});
    }

    // returns last item with x <= max_x
    item bsearch(ll max_x){
        auto it = s.lower_bound({max_x+1, -INFL});
        if(it == s.begin())
            return {INFL, -INFL};
        
        it--;
        return *it;
        
    }
};