/*
from https://github.com/defnotmee/definitely-not-a-lib
*/

#ifndef O_O
#include"../../template.cpp"
#include"rooted_tree.hpp"
#include"../../data structures/segtree_lazy.hpp"
#endif

struct HLD : Tree {
    private:
    SegTree st;
    vector<int> head;

    public:

    HLD(int n, int root = 0) : Tree(n, root), st(n), head(n) {}

    void calc_tree(){
        assert(m == n-1);
        prec(root);
        hld(root,root);
    }

    void calc_tree(vector<ll>& v){
        calc_tree();
        vector<ll> v2(n);
        for(int i = 0; i < n; i++)
            v2[tin[i]] = v[i];
        st = SegTree(v2);
    }

    int lca(int a, int b){
        while(head[a] != head[b]){
            if(tin[a] < tin[b])
                swap(a,b);
            a = pai[head[a]];
        }
        return min(a,b,[&](int a, int b){
            return tin[a] < tin[b];
        });
    }

    int dist(int a, int b){
        return height[a] + height[b] - 2*height[lca(a,b)];
    }

    using lazy = SegTree::lazy;
    using seg = SegTree::seg;

    void update_point(int id, SegTree::lazy upd){
        st.update(tin[id], tin[id], upd);
    }

    // if no_root = 1, the root won't be included in the update;
    void update_subtree(int id, SegTree::lazy upd, int no_root = 0){
        st.update(tin[id]+no_root, tout[id], upd);
    }

    // if no_root = 1, the root won't be included in the update;
    void update_path(int a, int b, SegTree::lazy upd, int no_root = 0){
        while(head[a] != head[b]){
            if(tin[a] < tin[b])
                swap(a,b);
            st.update(tin[head[a]], tin[a], upd);
            a = pai[head[a]];
        }
        if(tin[a] > tin[b])
            swap(a,b);
        st.update(tin[a]+no_root, tin[b], upd);
    }

    seg query_point(int id){
        return st.query(tin[id],tin[id]);
    }

    // if no_root = 1, the root won't be included in the query;
    seg query_subtree(int id, int no_root = 0){
        return st.query(tin[id]+no_root,tout[id]);
    }
    
    // if no_root = 1, the root won't be included in the query;
    // this query will work even if the query is non commutative
    seg query_path(int a, int b, int no_root = 0){
        seg retl = seg(), retr = seg();

        while(head[a] != head[b]){
            seg& ret = tin[a] > tin[b] ? retl : retr;
            int& v = tin[a] > tin[b] ? a : b;
            ret = st.merge(ret,st.query(tin[head[v]], tin[v]));
            v = pai[head[v]];
        }

        if(tin[a] > tin[b])
            swap(a,b);

        return st.merge(st.merge(retl,st.query(tin[a]+no_root,tin[b])), retr);

    }

    private:
    
    void prec(int id){
        // tout[id] = tin[id];
        if(g[id].size() && g[id][0] == pai[id]) // not on rooted_tree.hpp
            swap(g[id][0], g[id].back());// not on rooted_tree.hpp
        for(int& v : g[id]){ // & not in rooted_tree.hpp
            if(v == pai[id])
                continue;
            pai[v] = id;
            height[v] = height[id]+1;
            // tin[v] = tout[id]+1;
            prec(v);
            // tout[id] = tout[v];
            sub[id]+=sub[v];
            if(sub[v] > sub[g[id][0]]) // not on rooted_tree.hpp
                swap(v,g[id][0]); // not on rooted_tree.hpp
        }
    }

    void hld(int id, int hd){
        tout[id] = tin[id];
        head[id] = hd;
        if(g[id].size() && g[id][0] != pai[id]){
            tin[g[id][0]] = tout[id]+1;
            hld(g[id][0],hd);
            tout[id] = tout[g[id][0]];
        }
        for(int i = 1; i < g[id].size(); i++){
            int v = g[id][i];
            if(v == pai[id])
                continue;
            tin[v] = tout[id]+1;
            hld(v, v);
            tout[id] = tout[v];
        }
    }
};