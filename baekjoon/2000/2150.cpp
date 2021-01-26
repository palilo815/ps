#include <bits/stdc++.h>
using namespace std;

template <typename edge_t>
class sorted_edges {
public:
    sorted_edges(int n, const vector<pair<int, edge_t>>& edges) : start(n + 1), elist(edges.size()) {
        for (auto& e : edges)
            ++start[e.first + 1];
        partial_sum(start.begin(), start.end(), start.begin());

        auto counter = start;
        for (auto& e : edges)
            elist[counter[e.first]++] = e.second;
    }
    template <class UnaryFunction>
    void for_edge(int u, UnaryFunction f) {
        for_each(elist.begin() + start[u], elist.begin() + start[u + 1], [&](edge_t& e) { f(e); });
    }

private:
    vector<int> start;
    vector<edge_t> elist;
};

template <typename edge_t>
vector<vector<int>> scc(int n, vector<pair<int, edge_t>> edges) {
    auto elist = sorted_edges(n, edges);

    int t = 0, scc_cnt = 0;
    vector<int> stk, low(n), disc(n, -1), ids(n);

    auto dfs = [&](auto self, int u) -> void {
        low[u] = disc[u] = t++;
        stk.emplace_back(u);

        elist.for_edge(u, [&](int& v) {
            if (disc[v] == -1) {
                self(self, v);
                low[u] = min(low[u], low[v]);
            } else
                low[u] = min(low[u], disc[v]);
        });

        if (low[u] == disc[u]) {
            for (;;) {
                int x = stk.back();
                stk.pop_back();
                disc[x] = n;
                ids[x] = scc_cnt;
                if (x == u) break;
            }
            ++scc_cnt;
        }
    };

    for (int i = 0; i < n; ++i)
        if (disc[i] == -1)
            dfs(dfs, i);

    vector<vector<int>> ret(scc_cnt);
    for (int i = 0; i < n; ++i)
        ret[ids[i]].emplace_back(i);
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> edges(m);
    for (auto& [u, v] : edges)
        cin >> u >> v, --u, --v;

    auto ans = scc(n, edges);
    sort(ans.begin(), ans.end(), [&](auto& a, auto& b) {
        return *a.begin() < *b.begin();
    });

    cout << ans.size() << '\n';
    for (auto& v : ans) {
        for (auto& x : v) cout << x + 1 << ' ';
        cout << "-1\n";
    }
}