#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e5;

vector<int> adj[mxN];
bitset<mxN> bset;
int group[mxN];

int find_cycle(int u, int p) {
    bset[u] = true;
    for (int& v : adj[u]) {
        if (v == p) continue;
        if (bset[v]) return group[u] = -1, v;

        int ret = find_cycle(v, u);
        if (~ret) {
            if (ret != -2) group[u] = -1;
            return ret == u ? -2 : ret;
        }
    }
    return -1;
}
void grouping(int u, int g) {
    group[u] = g;
    bset[u] = true;
    for (int& v : adj[u])
        if (!bset[v])
            grouping(v, g);
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, q;
    cin >> n >> q;

    for (int i = 0, u, v; i < n; ++i) {
        cin >> u >> v;
        --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    find_cycle(0, -1);

    bset.reset();
    for (int i = 0; i < n; ++i)
        if (group[i] == -1)
            bset[i] = true;

    for (int i = 0; i < n; ++i)
        if (group[i] == -1)
            grouping(i, i);

    for (int u, v; q--;) {
        cin >> u >> v;
        cout << (group[u - 1] == group[v - 1] ? 1 : 2) << '\n';
    }
}