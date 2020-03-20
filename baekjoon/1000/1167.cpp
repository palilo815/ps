#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> tup;

const int max_V = 100000;

vector<tup> adj[max_V + 1];

int DFS(int u, int p) {
    int ret = 0;
    for (auto& [w, v, h] : adj[u]) if(v != p) {
        if (!h) h = DFS(v, u);
        ret = max(ret, h + w);
    }
    return ret;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V; cin >> V;
    for (int i = 1; i <= V; ++i) {
        int u, v, w;
        cin >> u;
        while (1) {
            cin >> v;
            if (v == -1) break;
            cin >> w;
            adj[u].emplace_back(w, v, 0);
        }
    }
    
    int ans = 0;
    for (int i = 1; i <= V; ++i)
        ans = max(ans, DFS(i, 0));
    cout << ans;
    return 0;
}