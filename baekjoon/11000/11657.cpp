#include <bits/stdc++.h>
using namespace std;

template <typename T, typename edge_t>
vector<pair<T, int>> bellman_ford(int n, vector<edge_t>& edges, int s) {
    const T inf = numeric_limits<T>::max();

    vector nodes(n, pair(inf, -1));
    nodes[s].first = 0;

    sort(edges.begin(), edges.end(), [&](const auto& lhs, const auto& rhs) {
        return (lhs.u < lhs.v ? lhs.u : ~lhs.u) < (rhs.u < rhs.v ? rhs.u : ~rhs.u);
    });

    const int lim = n / 2 + 2;
    for (int i = 0; i < lim; ++i)
        for (const auto& e : edges) {
            auto &cur = nodes[e.u], &dest = nodes[e.v];
            if (abs(cur.first) == inf) continue;
            if (T d = cur.first + e.w; d < dest.first) {
                dest.second = e.u;
                dest.first = (i == lim - 1 ? -inf : d);
            }
        }

    for (int i = 0; i < lim; ++i)
        for (const auto& e : edges)
            if (nodes[e.u].first == -inf)
                nodes[e.v].first = -inf;

    return nodes;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, m;
    cin >> n >> m;

    struct edge {
        int u, v, w;
    };

    vector<edge> edges(m);
    for (auto& [u, v, w] : edges)
        cin >> u >> v >> w, --u, --v;

    auto res = bellman_ford<int64_t>(n, edges, 0);

    if (find_if(res.begin(), res.end(), [&](auto& x) { return x.first == -LLONG_MAX; }) != res.end())
        return cout << -1, 0;

    for (int i = 1; i < n; ++i)
        cout << (res[i].first == LLONG_MAX ? -1 : res[i].first) << '\n';
}