#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

constexpr int MX_N = 300;

int adj[MX_N][MX_N], par[MX_N];
bool rev[MX_N], erased[MX_N][MX_N];

/* <dsu> */
int find(int u) {
    return par[u] < 0 ? u : par[u] = find(par[u]);
}
bool unite(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;

    if (par[u] > par[v]) swap(u, v);
    par[u] += par[v];
    par[v] = u;
    return true;
}
/* </dsu> */

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    vector<pair<int, int>> edges, added;

TOP:;
    int n;
    cin >> n;
    if (!n) return 0;

    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j) {
            cin >> adj[i][j];
            adj[j][i] = adj[i][j];
        }

    int ans = INT_MAX;
    for (int leaf = 0; leaf < n; ++leaf) {
        for (int i = 0; i < n; ++i)
            rev[i] = adj[leaf][i] > 0;

        edges.clear();
        int red_sum = 0;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if ((adj[i][j] > 0) ^ rev[i] ^ rev[j]) {
                    edges.emplace_back(i, j);
                    red_sum += abs(adj[i][j]);
                }

        int red_count = edges.size();
        for (int i = 0; i < n; ++i) {
            if (i == leaf) continue;
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                if ((adj[i][j] > 0) ^ rev[i] ^ rev[j]) {
                    erased[i][j] = erased[j][i] = true;
                    red_sum -= abs(adj[i][j]), --red_count;
                } else {
                    added.emplace_back(i, j);
                    red_sum += abs(adj[i][j]), ++red_count;
                }
            }

            if (red_count == n - 1 && red_sum < ans) {
                fill(par, par + n, -1);
                if (all_of(edges.begin(), edges.end(), [&](const auto& edge) { return erased[edge.first][edge.second] || unite(edge.first, edge.second); }) &&
                    all_of(added.begin(), added.end(), [&](const auto& edge) { return unite(edge.first, edge.second); }))
                    ans = red_sum;
            }

            added.clear();
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                if ((adj[i][j] > 0) ^ rev[i] ^ rev[j]) {
                    erased[i][j] = erased[j][i] = false;
                    red_sum += abs(adj[i][j]), ++red_count;
                } else {
                    red_sum -= abs(adj[i][j]), --red_count;
                }
            }
        }
    }
    cout << (ans == INT_MAX ? -1 : ans) << '\n';
    goto TOP;
}