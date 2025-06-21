/**
 * from https://github.com/defnotmee/definitely-not-a-lib
 */
#ifndef O_O
#include"../utility/template.cpp"
#include"../utility/rng.hpp"
#endif

struct IncrementalMST{
    vector<int> par, sz, prio;
    vector<pii> parw;
    

    IncrementalMST(int n) : par(n), sz(n,1), prio(n), parw(n,{INF,INF}){
        iota(all(prio),0);
        par = prio;
        shuffle(all(prio),rng);
    }
    private:

    int find(int v, pii w = {INF-1,INF}){
        while(parw[v] <= w){
            while(parw[v] > parw[par[v]]){
                sz[par[v]]-=sz[v];
                par[v] = par[par[v]];
            }
            v = par[v];
        }
        return v;
    }

    void disconnect(int v){
        if(par[v] == v)
            return;
        disconnect(par[v]);
        sz[par[v]]-=sz[v];
    }

    int connect(int v, pii w = {INF-1, INF}){
        while(parw[v] <= w){
            sz[par[v]]+=sz[v];
            v = par[v];
        }
        return v;
    }

    void consider_edge(int a, int b, pii w){
        disconnect(a), disconnect(b);

        while(a != b){
            a = connect(a,w);
            b = connect(b,w);
            if(prio[a] > prio[b])
                swap(a,b);
            swap(par[a],b);
            swap(parw[a],w);
        }
        
        // connect(a);
    }

    public:

    /**
     * Finds maximum edge in the path from a to b
     * @return weight of maximum edge from a to b (or {INF,-1} if
     * they are disconnected)
     */
    pii max_edge(int a, int b){
        int ra = find(a), rb = find(b);
        if(ra != rb)
            return {INF,-1};

        if(parw[a] > parw[b])
            swap(a,b);
        while(par[a] != b){
            a = par[a];
            if(parw[a] > parw[b])
                swap(a,b);
        }
        return parw[a];
    }

    /**
     * Deletes maximum edge of the path from a to b
     * from the MST
     * @return weight of the edge removed from the MST (or {INF,-1} if
     * they are disconnected)
     */
    pii delete_maximum(int a, int b){
        int ra = find(a), rb = find(b);
        if(ra != rb)
            return {INF,-1};

        if(parw[a] > parw[b])
            swap(a,b);
        while(par[a] != b){
            a = par[a];
            if(parw[a] > parw[b])
                swap(a,b);
        }

        b = a;
        while(par[b] != b){
            sz[par[b]]-=sz[a];
            b = par[b];
        }
        par[a] = a;
        pii ret = {INF,INF};
        swap(parw[a],ret);
        return ret;
    }

    /**
     * Adds edge between a and b with weight w to the graph.
     * @return weight of the edge removed from the MST (or {INF,-1} if
     * there was none)
     */
    pii add_edge(int a, int b, pii w){
        if(a == b)
            return {INF,-1};
        
        pii ret = delete_maximum(a,b);
        if(ret <= w)
            swap(w,ret);
        
        consider_edge(a,b,w);

        return ret;
    }
};