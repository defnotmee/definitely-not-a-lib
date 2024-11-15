/*
from https://github.com/defnotmee/definitely-not-a-lib

Offline Dynamic Connectivity in O(nlog^2(n)). Allows for duplicate edges.
If an edge that doesn't exist is deleted, it is just ignored.

By default answers how many connected components were in the graph at
a given point.
*/

#ifndef O_O
#include"../utility/template.cpp"
#include"dsu_rollback.hpp"
#endif

struct Dynamic_Connectivity{
    int n;
    DSU_Rollback uf;
    vector<pii> edges;
    vector<int> ponta;
    map<pii, basic_string<int>> st;

    Dynamic_Connectivity(int n = 0, int expected = 0) : n(n), uf(n){
        ponta.reserve(expected);
        edges.reserve(expected);
    }

    void add_edge(int a, int b){
        if(a > b)
            swap(a,b);
        st[{a,b}].push_back(edges.size());
        edges.push_back({a,b});
        ponta.push_back(-2);
    }

    void rem_edge(int a, int b){
        if(a > b)
            swap(a,b);
        if(st[{a,b}].empty()) // removing edge that is not there
            return;
        int removed = st[{a,b}].back();
        st[{a,b}].pop_back();
        
        ponta[removed] = edges.size();
        ponta.push_back(removed);
        edges.push_back({a,b});
    }

    void add_query(){
        edges.push_back({-1,-1});
        ponta.push_back(-1);
    }


    vector<int> solve(){
        for(int& i : ponta)
            if(i == -2) i = ponta.size();
        
        vector<int> resp;

        solve(0, int(ponta.size())-1,resp);

        return resp;
    }

    private:

    void solve(int l, int r, vector<int>& resp){

        if(l == r){
            if(ponta[l] == -1){
                resp.push_back(uf.comp_ct);
            }
            return;
        }

        int version = uf.snapshot();

        int m = (l+r)>>1;

        for(int i = m+1; i <= r; i++){
            if(ponta[i] < l){
                uf.onion(edges[i].ff, edges[i].ss);
            }
        }

        solve(l,m,resp);

        while(uf.snapshot() != version)
            uf.rollback();

        for(int i = l; i <= m; i++){
            if(ponta[i] > r){
                uf.onion(edges[i].ff,edges[i].ss);
            }
        }

        solve(m+1,r,resp);

        while(uf.snapshot() != version)
            uf.rollback();
    }
};