#include <bits/stdc++.h>
using namespace std;

const int max_N = 2000;

vector<int> adj[max_N];
bool visited[max_N];

int DFS(int u) {
    int ret = 1;
    visited[u] = true;
    for (int v : adj[u]) if (!visited[v]) {
        ret = max(ret, DFS(v) + 1);
        if (ret >= 5) return ret;
    }
    visited[u] = false;
    return ret;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    for (int i = 0; i < N; ++i)
        if (DFS(i) >= 5) {
            cout << 1;
            return 0;
        }
    cout << 0;
    return 0;
}