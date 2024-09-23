/*
from https://github.com/defnotmee/definitely-not-a-lib

With O(nlog(n)) pre-processing, creates a data structure that
answers minimum range queries (RMQ) in O(1). Can be modified
to work with any indempotent function.


*/

#ifndef O_O
#include"../utility/template.cpp"
#endif

template<typename T = int>
struct RMQ{
    int n;
    vector<vector<T>> sp;

    RMQ(vector<T> v) : n(v.size()), sp(int(log2(n))+1, vector<T>(n)){
        sp[0] = v;

        for(int i = 1; i < sp.size(); i++)
            for(int j = 0; j + (1<<i) <= n; j++)
                sp[i][j] = merge(sp[i-1][j], sp[i-1][j+(1<<i-1)]);

    }

    static T merge(T a, T b){
        return min(a,b);
    }

    T query(int l, int r){ // must be called with l <= r
        int logg = log2(r-l+1);
        return merge(sp[logg][l], sp[logg][r-(1<<logg)+1]);
    }
};