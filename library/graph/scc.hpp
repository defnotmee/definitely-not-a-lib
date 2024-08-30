/*
from https://github.com/defnotmee/definitely-not-a-lib

Implements kosaraju's algorithm for finding strongly connected
components. 

Usage:
SCC(n) : prepares graph of size n with vertices from 0 to n-1
add_edge(a,b) : adds directed edge from a to b

After adding all the edges, call kosaraju().

This call will make SCC::scc have information 
on the strongly connected components:

(I) 0 <= scc[i] < scc_count
(II) scc[i] = scc[j] <=> there is a path from i to j and from j to i.
(III) scc[i] < scc[j] => there is no path from j to i. [bonus from kosaraju!]

get_condensation() will return a graph of the scc's (condensation graph).
It will be a DAG!

fun fact: if you want to dp in the condensation graph you don't need to dfs,
you can just process the sccs in **descending** order because of property (III)!
*/

#ifndef O_O
#include"../utility/template.cpp"
#endif

struct SCC{

    int n;
    vector<bstring<int>> g, r;

    vector<int> scc;
    int scc_count = 0;

    SCC(int n = 0) : n(n), g(n), r(n), scc(n,-1){}

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

    struct Condensation{
        int n; // number of nodes
        int sn; // number of sccs
        vector<bstring<int>> g; // Edges going out of the scc
        vector<bstring<int>> in_scc; // List of vertices in scc[i]

        Condensation(int n, int sn) : n(n), sn(sn), g(sn), in_scc(sn){};
    };

    Condensation get_condensation(){
        if(scc.back() == -1)
            kosaraju();

        Condensation ret(n,scc_count);

        for(int i = 0; i < n; i++){
            ret.in_scc[scc[i]].push_back(i);
            for(int j : g[i]){
                if(scc[j] != scc[i])
                    ret.g[scc[i]].push_back(scc[j]);
            }
        }

        // comment if you dont care about repeated edges
        for(int i = 0; i < scc_count; i++){
            sort(all(ret.g[i]));
            ret.g[i].erase(unique(all(ret.g[i])),ret.g[i].end());
        }
        return ret;
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