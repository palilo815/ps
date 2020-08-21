#include <bits/stdc++.h>
using namespace std;

const int mx = 1e4 + 1;
const int INF = 0x3f3f3f3f;

vector<int> adj[mx];
int dist[mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 1, M; i <= N; ++i) {
        cin >> M;
        adj[i] = vector<int>(M);
        for (auto& x : adj[i]) cin >> x;
    }

    memset(dist + 1, 0x3f, sizeof(int) * N);
    dist[1] = 1;

    queue<int> q;
    q.emplace(1);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int& v : adj[u])
            if (dist[v] == INF) {
                dist[v] = dist[u] + 1;
                q.emplace(v);
            }
    }

    bool Y = true;
    int ans = INF;
    for (int i = 1; i <= N; ++i)
        if (dist[i] == INF) Y = false;
        else if (adj[i].empty() && dist[i] < ans) ans = dist[i];
    cout << (Y ? "Y\n" : "N\n") << ans;
    return 0;
}