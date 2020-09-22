#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

vector<int> adj[mxN];
int prv[mxN], nxt[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;
    for (int i = 1, u, v; i < N; ++i) {
        cin >> u >> v;
        adj[u - 1].emplace_back(v - 1);
    }

    vector<int> vt;
    vector<bool> visited(N);
    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        for (int& v : adj[u])
            if (!visited[v])
                dfs(v);
        vt.emplace_back(u);
    };

    for (int i = 0; i < N; ++i)
        if (!visited[i])
            dfs(i);

    for (int& u : vt) {
        nxt[u] = adj[u].size();
        for (int& v : adj[u])
            nxt[u] += nxt[v];
    }
    for (auto it = vt.rbegin(); it != vt.rend(); ++it) {
        int& u = *it;
        for (int& v : adj[u])
            prv[v] += prv[u] + 1;
    }

    for (int i = 0; i < N; ++i)
        if (prv[i] && prv[i] + nxt[i] == N - 1)
            cout << i + 1 << '\n';
    return 0;
}