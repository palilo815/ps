#include <bits/stdc++.h>
using namespace std;

const int max_N = 200000;

bool visited[max_N + 1];
vector<int> adj[max_N + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }

    queue<int> q;
    q.push(1), q.push(-1);
    visited[1] = true;
    int ans = 0;

    while (1) {
        int u = q.front(); q.pop();

        if (u == -1) {
            if (q.empty()) { ans = -1; break; }
            ++ans; q.push(-1);
            continue;
        }
        if (u == N) break;

        for (int v : adj[u]) if (!visited[v]) {
            visited[v] = true;
            q.push(v);
        }
    }
    cout << ans;
    return 0;
}