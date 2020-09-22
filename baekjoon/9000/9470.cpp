#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e3;

vector<int> adj[mxN];
int str[mxN], cnt[mxN];

void solve() {
    int T, N, M;
    cin >> T >> N >> M;

    vector<bool> in(N);
    memset(str, 0, sizeof(int) * N);
    memset(cnt, 0, sizeof(int) * N);
    for (int i = 0; i < N; ++i)
        adj[i].clear();

    for (int u, v; M--;) {
        cin >> u >> v;
        --u, --v;
        adj[u].emplace_back(v);
        in[v] = true;
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

    for (auto it = vt.rbegin(); it != vt.rend(); ++it) {
        int& u = *it;
        str[u] = in[u] ? (str[u] + (cnt[u] > 1)) : 1;
        for (int& v : adj[u])
            if (str[u] > str[v])
                str[v] = str[u], cnt[v] = 1;
            else if (str[u] == str[v])
                ++cnt[v];
    }
    cout << T << ' ' << str[vt[0]] << '\n';
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}