/*
from https://github.com/defnotmee/definitely-not-a-lib

Constructs a functional graph. Is able to answer distance directed distance
queries in O(1).

For each vertex stores the following information

- pai[v]: parent of a vertex
- height[v]: ammount of steps necessary to reach a vertex on a cycle
- cycleid[v]: which cycle v ends up in. If cycleid[v] != cycleid[u], they are on different components
- cyclepos[v]: index of the first vertex from the cycle that v touches on clist[cycleid[v]]
- tin[v]: preorder of v on its corresponding tree (rooted on clist[cycleid[v]][cyclepos[v]])
- tout[v]: preorder of v on its corresponding tree (rooted on clist[cycleid[v]][cyclepos[v]])

In addition, for each cycle, stores a list of the vertices in the cycle on clist[v]

All of this is O(n) preprocessing.
*/

#ifndef O_O
#include"template.cpp"
#endif

struct FuncGraph{
    int n;
    vector<int> pai, height, cycleid, cyclepos, is_cycle, tin, tout;
    vector<bstring<int>> rev, clist;

    FuncGraph(vector<int> v) : n(v.size()), pai(v), height(n), 
    rev(n), cycleid(n,-1), cyclepos(n), clist(n), is_cycle(n), tin(n), tout(n){
        for(int i = 0; i < n; i++)  
            rev[pai[i]].push_back(i);

        for(int i = 0; i < n; i++){
            if(cycleid[i] == -1)
                get_cycle(i);
        }
    }

    void get_cycle(int id){
        int a = id, b = id;

        do{
            a = pai[a];
            b = pai[pai[b]];
        } while(a != b);

        process_cycle(a);
    }

    void process_cycle(int id){
        int cid = cycleid[id] = id;


        int v = id;
        do{
            cyclepos[v] = clist[cid].size();
            clist[cid].push_back(v);
            is_cycle[v] = 1;
            v = pai[v];
            cycleid[v] = cid;
        } while(v != id);

        do{
            dfs(v);
            v = pai[v];
        } while(v != id);

    }

    void dfs(int id){
        tout[id] = tin[id];
        for(int i : rev[id]){
            if(cycleid[i] == -1){
                cycleid[i] = cycleid[id];
                cyclepos[i] = cyclepos[id];
                height[i] = height[id]+1;
                tin[i] = ++tout[id];
                dfs(i);
                tout[id] = tout[i];
            }
        }
    }

    // returns distance from a to b, or INF if its not possible to go from a to b
    int dist(int a, int b){
        if(cycleid[a] != cycleid[b])
            return INF;
        if(is_cycle[a] && !is_cycle[b])
            return INF;
        if(!is_cycle[a] && !is_cycle[b]){
            if(height[a] < height[b] || cyclepos[a] != cyclepos[b])
                return INF;
            if(tin[b] <= tin[a] && tin[a] <= tout[b]){
                return height[a]-height[b];
            }
            return INF;
        }

        return height[a]+dist_in_cycle(cyclepos[a], cyclepos[b], clist[cycleid[a]].size());
    }

    private:

    int dist_in_cycle(int a, int b, int csize){
        if(b >= a)
            return b-a;
        return csize+b-a;
    }

};