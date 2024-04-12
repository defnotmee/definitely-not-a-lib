/*
from https://github.com/defnotmee/definitely-not-a-lib

Maintains a partially ordered set (or pareto front), that is,
a list of pairs (x[i], y[i]) such that if for i < j:
x[i] < x[j], then y[i] < y[j].

In a practical sense, "increasing x is bad but incresing y
is good". You can edit pareto::item::fix to change that.

Can only do insertions. O(logn) per insert.
*/

#ifndef O_O
#include"template.cpp"
#endif

struct pareto{
    struct item{
        ll x, y;

        bool operator<(item c) const {
            if(x == c.x)
                return y < c.y;
            return x < c.x;
        }

        
        inline void fix(){
            // In case increasing x is good, uncomment this:
            // x*=-1;

            // In case increasing y is bad, uncomment this:
            // y*=-1;
            
        }
    };

    set<item> s;

    void insert(ll x, ll y){
        item cur = {x,y};
        cur.fix();
        auto it = s.lower_bound(cur);

        if(it != s.begin()){
            auto it2 = it;
            it2--;

            if(it2->y >= cur.y)
                return;
        }

        while(it != s.end() && cur.y >= it->y){
            it = s.erase(it);
        }

        s.insert(cur);
    }

    // returns last item with x <= max_x
    item bsearch(ll max_x){
        item cur = {max_x,0};
        cur.fix();
        cur.x++;
        cur.y = -INFL;
        auto it = s.lower_bound(cur);
        if(it == s.begin()){
            item ret = {INFL,-INFL};
            ret.fix();
            return ret;
        }
        it--;
        item ret = *it;
        ret.fix();
        return ret;
        
    }
};