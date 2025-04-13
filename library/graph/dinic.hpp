/**
 * from https://github.com/defnotmee/definitely-not-a-lib
 * Based on https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/Dinic.h
 * 
 * Uses Dinic's algorithm to find maximum flow between two vertices.
 * 
 * O(VElog(U)), where U is max capacity. Faster in practice. On unit networks
 * (graphs where capacities not connected to source or sink are 1), complexity
 * improves to O(sqrt(V)E).
 * 
 * After calling max_flow, the corresponding flow on edges is recoverable
 * with Edge::flow() and left_of_mincut becomes well defined.
 */

#ifndef O_O
#include"../utility/template.cpp"
#endif


struct Dinic{
    struct Edge{
        ll to, cap, ocap, rev;
        ll flow(){
            return max(ocap-cap, 0ll);
        }
    };

    vector<vector<Edge>> g;

    void add_edge(int u, int v, ll cap){
        g[u].push_back({v,cap,cap,(ll)g[v].size()});
        g[v].push_back({u, 0, 0, (ll)g[u].size()-1});
    }

    // Returns if v is in the same side of the min_cut as s
    bool left_of_mincut(int v){
        return dist[v] != -1;
    }

    ll max_flow(int s, int t){
        ll flow = 0;
        for(int k = 30; k >= 0; k--)
            while(bfs(s,t,k)) while (ll it = dfs(s,t,LLONG_MAX)) flow += it;
        return flow;
    }

    Dinic(int n) : g(n), ptr(n), dist(n){}

    private:
    vector<int> ptr, dist;

    ll dfs(int id, int t, ll x){
        if(id == t || !x)
            return x;

        for(int & i =ptr[id]; i < g[id].size(); i++){
            Edge& e = g[id][i];
            if(dist[e.to] != dist[id]+1)
                continue;
            if(ll filled = dfs(e.to, t, min(x, e.cap))){
                e.cap-=filled;
                g[e.to][e.rev].cap+=filled;
                return filled;
            }
        }

        return 0;
    }

    bool bfs(int s, int t, int k){
        fill(all(ptr),0), fill(all(dist),-1);
        vector<int> q({s});
        q.reserve(g.size());
        dist[s] = 0;
        for(int i = 0; i < q.size(); i++){
            int id = q[i]; 
            for(auto i : g[id]){
                if(dist[i.to] == -1 && (i.cap>>k)){
                    dist[i.to] = dist[id]+1;
                    q.push_back(i.to);
                }
            }
        }
        return dist[t]+1;
    }    
};