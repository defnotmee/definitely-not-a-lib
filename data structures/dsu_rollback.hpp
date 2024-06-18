/*
from https://github.com/defnotmee/definitely-not-a-lib
*/

#ifndef O_O
#include"template.cpp"
#endif

struct DSU_Rollback{
    struct log{
        int node1, node2;
        int prev1, prev2;
    };
    private:
    vector<int> v; // Either parent (if v[i] >= 0) or size (if v[i] < 0 and i is a root) of the component
    vector<log> history;
    public:
    
    constexpr int size(int id){ // Only call when id is the root of a group. Use size(find(id)) otherwise.
        return -v[id];
    }

    constexpr int pai(int id){ // Returns parent of id
        return v[id] < 0 ? id : v[id];
    }

    DSU_Rollback(int n = 0) : v(n,-1){}

    int find(int id){ // removing path compression
        return v[id] < 0 ? id : find(v[id]);
    }

    bool onion(int a, int b){
        a = find(a);
        b = find(b);

        if(a == b)
            return 0;

        if(size(a) > size(b)) // union by size
            swap(a,b);

        history.push_back({a,b,v[a],v[b]});
        v[b] += v[a];
        v[a] = b;
        return 1;
    }

    void rollback(){
        auto [a,b,va,vb] = history.back();
        v[a] = va;
        v[b] = vb;
        history.pop_back();
    }

    bool same(int a, int b){
        return find(a) == find(b);
    }

    int snapshot(){
        return history.size();
    }
    
};