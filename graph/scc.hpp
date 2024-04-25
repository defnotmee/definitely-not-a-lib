/*
from https://github.com/defnotmee/definitely-not-a-lib

Implements kosaraju algorithm for finding strongly connected
components. 

Usage:
SCC(n) : prepares graph of size n with vertices from 0 to n-1
add_edge(a,b) : adds directed edge from a to b

After adding all the edges, call kosaraju()

SCC::scc scc will have information 
on the strongly connected components:

+ 0 <= scc[i] < scc_count
+ scc[i] = scc[j] <=> i and j are on the same SCC
+ scc[i] < scc[j] => there is no path from j to i.

*/

#ifndef O_O
#include"template.cpp"
#endif

struct SCC{

    int n;
    vector<bstring<int>> g, r;

    vector<int> scc;
    int scc_count = 0;

    SCC(int n = 0) : n(n), g(n), r(n), scc(n){}

    void add_edge(int a, int b){
        g[a].push_back(b);
        r[b].push_back(a);
    }

    void kosaraju(){
        vector<int> check(n);

        vector<int> euler;
        euler.reserve(n);

        for(int i = 0; i < n; i++)
            if(!check[i]) dfs(i,check,euler);

        reverse(all(euler));

        for(int i : euler)
            if(check[i] == 1) rdfs(i,check), scc_count++;
    }

    private:

    void dfs(int id, vector<int>& check, vector<int>& euler){
        check[id] = 1;
        for(int i : g[id])
            if(!check[i]) 
                dfs(i,check,euler);
        euler.push_back(id);
    }

    void rdfs(int id, vector<int>& check){
        scc[id] = scc_count;
        check[id] = 2;
        for(int i : r[id])
            if(check[i] == 1)
                rdfs(i,check);
    }

    
};