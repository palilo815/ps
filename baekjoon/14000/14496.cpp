#include <bits/stdc++.h>
using namespace std;

const int max_N = 1000;

vector<int> adj[max_N + 1];
bool visited[max_N + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int src, dst, N, M;
    cin >> src >> dst >> N >> M;
    while (M--) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    queue<int> q;
    q.emplace(src), q.emplace(-1);
    int ans = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == -1) {
            if (q.empty()) {
                ans = -1; break;
            }
            ++ans; q.emplace(-1);
            continue;
        }
        if (u == dst) break;
        
        for (int v : adj[u]) if (!visited[v]) {
            visited[v] = true;
            q.emplace(v);
        }
    }
    cout << ans;
    return 0;
}