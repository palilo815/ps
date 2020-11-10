#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

vector<int> adj[mxN];
int sz[mxN];

void dfs(int u) {
    if (adj[u].empty()) {
        sz[u] = 1;
        return;
    }

    for (int& v : adj[u]) dfs(v);
    auto heavy = *max_element(adj[u].begin(), adj[u].end(), [&](auto& a, auto& b) {
        return sz[a] < sz[b];
    });

    sz[u] = sz[heavy] + 1;
    sz[heavy] = 0;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, K;
    cin >> N >> K;

    for (int i = 1, p; i < N; ++i) {
        cin >> p;
        adj[p - 1].emplace_back(i);
    }

    dfs(0);

    sort(sz, sz + N, greater<int>());
    cout << accumulate(sz, sz + K, 0);
}