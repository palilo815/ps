#include <bits/stdc++.h>
using namespace std;

const int max_N = 2000;

vector<int> adj[max_N + 1];
bool destroyed[max_N + 1];
bool check[max_N + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    int K; cin >> K;
    for (int i = 0; i < K; ++i) {
        int x; cin >> x;
        destroyed[x] = true;
    }

    vector<int> ans;
    for (int u = 1; u <= N; ++u) {
        if (!destroyed[u] || adj[u].size() >= K) continue;
        bool flag = false;
        for (int v : adj[u]) if (!destroyed[v]) {
            flag = true;
            break;
        }
        if (!flag) ans.emplace_back(u);
    }

    for (int u : ans) {
        check[u] = true;
        for (int v : adj[u])
            check[v] = true;
    }

    for (int i = 1; i <= N; ++i)
        if (destroyed[i] && !check[i]) {
            cout << -1;
            return 0;
        }

    cout << ans.size() << '\n';
    for (int u : ans) cout << u << ' ';
    return 0;
}