/*
from https://github.com/defnotmee/definitely-not-a-lib

Uses hopcroft-karp's algorithm to find the maximum matching on a
bipartite graph. Runs in time O(E*sqrt(V)) on worst case, and time
O(E*log(V)) on random graphs.

Depending on the aplication, the dinic.hpp interface may be more convenient.
*/

#ifndef O_O
#include"../utility/template.cpp"
#endif

struct BiGraph{ // bipartite graph of sizes n and m

    int n, m;
    vector<basic_string<int>> g;
    vector<int> matched, match;

    BiGraph(int _n, int _m) : n(_n), m(_m), g(n), matched(n), match(m,-1){}

    void add_edge(int a, int b){
        g[a].push_back(b);
    }

    vector<pii> max_matching(){

        while(augment());

        vector<pii> resp;
        for(int i = 0; i < m; i++)
            if(match[i] != -1)
                resp.push_back({match[i], i});
    
        return resp;
    }

    private:
    bool augment(){
        vector<int> dist(n, -1);

        queue<int> q;
        for(int i = 0; i < n; i++){
            if(!matched[i])
                q.push(i), dist[i] = 0;
        }

        bool fail = 1;
        while(!q.empty() && fail){
            int cur = q.front();
            q.pop();
            for(int i : g[cur]){
                if(match[i] == -1){
                    fail = 0;
                    break;
                }
                if(dist[match[i]] == -1){
                    dist[match[i]] = dist[cur]+1;
                    q.push(match[i]);
                }
            }
        }

        if(fail)
            return false;

        vector<int> check(n);

        auto dfs =[&](int id, auto && dfs) -> bool {
            check[id] = 1;
            for(int i : g[id]){
                int& mi = match[i];
                if(mi == -1 ||
                (!check[mi] && dist[mi] == dist[id]+1 && dfs(mi,dfs))){
                    mi = id;
                    matched[id] = 1;
                    return true;
                }
            }
            return false;
        };

        for(int i = 0; i < n; i++){
            if(!check[i] && !matched[i])
                dfs(i,dfs);
        }

        return true;
    }

};