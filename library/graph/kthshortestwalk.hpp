/**
 * from https://github.com/defnotmee/definitely-not-a-lib
 * 
 * Copied from https://judge.yosupo.jp/submission/246093
 * Thanks nor!!
 */
#ifndef O_O
#include"../utility/template.cpp"
#endif

template <class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

template <class Distance, class Graph>
auto dijkstra(const Graph& g, int s) {
    vector<Distance> d(g.size(), numeric_limits<Distance>::max());
    vector<Distance> prv(g.size(), -1);
    min_heap<pair<Distance, int>> heap;
    heap.emplace(d[s] = 0, s);
    while (!heap.empty()) {
        auto [dv, v] = heap.top();
        heap.pop();
        if (dv != d[v]) continue;
        for (auto&& [to, w] : g[v]) {
            if (d[to] > dv + w) {
                d[to] = dv + w;
                heap.emplace(d[to], to);
                prv[to] = v;
            }
        }
    }
    return make_pair(d, prv);
}

template <typename Key, typename Value>
struct LeftistHeap {
    using self_t = LeftistHeap<Key, Value>;
    int rank;
    Key key;
    Value value;
    self_t *left, *right;
    constexpr LeftistHeap(int rank_, Key key_, Value value_, self_t* left_,
                          self_t* right_)
        : rank{rank_}, key{key_}, value{value_}, left{left_}, right{right_} {}
    inline static deque<LeftistHeap> alloc;
    static self_t* insert(self_t* const a, const Key k, const Value v) {
        if (not a or k <= a->key) {
            alloc.emplace_back(1, k, v, a, nullptr);
            return &alloc.back();
        }
        auto l = a->left, r = insert(a->right, k, v);
        if (not l or r->rank > l->rank) swap(l, r);
        alloc.emplace_back(r ? r->rank + 1 : 0, a->key, a->value, l, r);
        return &alloc.back();
    }
};

template <typename Distance, typename Graph>
auto kth_shortest_paths(int n, const Graph& g, int source, int sink, int k) {
    Graph g_rev(n);
    for (int u = 0; u < n; ++u)
        for (auto [v, w] : g[u]) g_rev[v].push_back({u, w});
    auto [d, prv] = dijkstra<Distance>(g_rev, sink);
    if (d[source] == numeric_limits<Distance>::max())
        return vector<Distance>{};
    vector<basic_string<int>> tree(n);
    for (int u = 0; u < n; ++u)
        if (prv[u] != -1) tree[prv[u]].push_back(u);
    using heap_t = LeftistHeap<Distance, int>;
    vector<heap_t*> h(n, nullptr);
    {
        queue<int> q({sink});
        while (not q.empty()) {
            const int u = q.front();
            q.pop();
            bool seen_p = false;
            for (const auto [v, w] : g[u]) {
                if (d[v] == numeric_limits<Distance>::max()) continue;
                const auto c = w + d[v] - d[u];
                if (not seen_p and v == prv[u] and c == 0) {
                    seen_p = true;
                    continue;
                }
                h[u] = heap_t::insert(h[u], c, v);
            }
            for (auto v : tree[u]) h[v] = h[u], q.push(v);
        }
    }
    vector<Distance> ans{d[source]};
    ans.reserve(k);
    if (not h[source]) return ans;
    {
        min_heap<pair<Distance, heap_t*>> q;
        q.push({d[source] + h[source]->key, h[source]});
        while (not q.empty() and (int) ans.size() < k) {
            auto [cd, ch] = q.top();
            q.pop();
            ans.push_back(cd);
            if (h[ch->value]) q.push({cd + h[ch->value]->key, h[ch->value]});
            if (ch->left) q.push({cd + ch->left->key - ch->key, ch->left});
            if (ch->right) q.push({cd + ch->right->key - ch->key, ch->right});
        }
    }
    return ans;
}