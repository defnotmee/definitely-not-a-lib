/*
from https://github.com/defnotmee/definitely-not-a-lib
*/

#ifndef O_O
#include"template.cpp"
#include"scc.hpp"
#endif

struct TwoSat{
    int n;
    SCC scc;

    TwoSat(int n = 0) : n(n), scc(2*n){}

    static constexpr int no(int x){
        return 2*x;
    }
    static constexpr int yes(int x){
        return 2*x+1;
    }

    void add_or(int a, int b){
        scc.add_edge(a^1, b);
        scc.add_edge(b^1, a);
    }

    void add_xor(int a, int b){
        add_or(a,b);
        add_or(a^1,b^1);
    }

    // If impossible, returns an empty vector
    // If possible, returns a possible construction where
    // ret[i] = 1 <=> i is true
    vector<int> get_sat(){
        scc.kosaraju();
        vector<int> ret(n);

        for(int i = 0; i < n; i++){
            if(scc.scc[no(i)] == scc.scc[yes(i)])
                return {};
            ret[i] = scc.scc[no(i)] < scc.scc[yes(i)];
        }

        return ret;
    }

};