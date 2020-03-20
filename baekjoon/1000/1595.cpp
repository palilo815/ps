#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> tup;

const int max_V = 10000;

bool city[max_V + 1];
vector<tup> adj[max_V + 1];

int DFS(int u, int p) {
    int ret = 0;
    for (auto& [w, v, h] : adj[u]) if (v != p) {
        if (!h) h = DFS(v, u);
        ret = max(ret, h + w);
    }
    return ret;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int u, v, w;
    while (cin >> u >> v >> w) {
        adj[u].emplace_back(w, v, 0);
        adj[v].emplace_back(w, u, 0);
        city[u] = city[v] = true;
    }

    int ans = 0;
    for (int i = 1; i <= max_V; ++i) if (city[i])
        ans = max(ans, DFS(i, 0));
    cout << ans;
    return 0;
}