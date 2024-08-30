/*
from https://github.com/defnotmee/definitely-not-a-lib

Uses Dinic's algorithm to calculate the maximum flow between
s and t in a graph.

O(V^2E) in general, O(Esqrt(V)) on unit networks (edges that are
not connected to s or t have unit capacity, like in matching).

Usage: Declare FlowGraph(n,s,t) and add edges to it. When done, call
max_flow(). It returns the maximum flow between s and t. By default,
s = 0 and t = n-1.

After calling max_flow, the edges with EVEN indices on FlowGraph::edges
will have the "flow" variable corresponding to the ammount of flow passing
through them in the answer dinic provides.
*/

#ifndef O_O
#include"../utility/template.cpp"
#endif

struct FlowEdge {
    ll u, v, cap, flow = 0;

    ll to(ll id){
        return id == u ? v : u;
    }
};

struct FlowGraph{
    int n;
    int s, t;
    vector<FlowEdge> edges;

    vector<bstring<int>> g;

    FlowGraph(int n = 0, int _s = 0, int _t = -1) : n(n), s(_s), t(_t), g(n){
        if(t == -1)
            t = n-1;
    }

    void add_edge(ll u, ll v, ll cap){
        g[u].push_back(edges.size());
        edges.push_back({u,v,cap});
        g[v].push_back(edges.size());
        edges.push_back({v,u,0});
    }

    ll max_flow(){
        ll ret = 0;
        while(true){
            ll cur = block_flow();
            if(!cur)
                break;
            ret+=cur;
        }
        return ret;
    }

    private:
    vector<int> ptr, dist;
    ll block_flow(){
        ll ret = 0;
        dist = bfs();
        ptr = vector<int>(n);
        return dfs(s,INFL); // INFL needs to be >= than the max flow of the graph
    }

    vector<int> bfs(){
        vector<int> dist(n,n);

        queue<int> q;
        dist[s] = 0;
        q.push(s);

        while(!q.empty()){
            int cur = q.front();
            q.pop();
            for(int eid : g[cur]){
                FlowEdge cedge = edges[eid];
                int to = cedge.to(cur);

                if(cedge.cap == cedge.flow)
                    continue;
                
                if(dist[to] > dist[cur]+1){
                    dist[to] = dist[cur]+1;
                    q.push(to);
                }
            }
        }

        return dist;
    }

    ll dfs(int id, ll pushed){
        if(pushed == 0)
            return 0;
        if(id == t)
            return pushed;

        ll rem = pushed;

        while(rem && ptr[id] < g[id].size()){
            int eid = g[id][ptr[id]];
            int to = edges[eid].to(id);
            ptr[id]++;

            if(dist[id] >= dist[to])
                continue;

            ll usable = min(rem, edges[eid].cap-edges[eid].flow);
            ll used = dfs(to,usable);

            edges[eid].flow+=used;
            edges[eid^1].flow-=used;

            rem-=used;
        }
        return pushed-rem;
    }
};