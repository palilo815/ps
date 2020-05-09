#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int max_N = 40001;

vector<int> adj[max_N];
int d_Bessie[max_N];
int d_Elsie[max_N];
int d_both[max_N];
queue<int> q;

void BFS(int src, int N, int dist[]) {
    memset(dist + 1, 0x3f, sizeof(int) * N);
    dist[src] = 0;

    q.emplace(src);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) if (dist[v] > dist[u] + 1) {
            dist[v] = dist[u] + 1;
            q.emplace(v);
        }
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    ll B, E, P;
    int N, M;
    cin >> B >> E >> P >> N >> M;
    while (M--) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    BFS(1, N, d_Bessie);
    BFS(2, N, d_Elsie);
    BFS(N, N, d_both);

    ll ans = B * d_Bessie[N] + E * d_Elsie[N];
    for (int i = 1; i <= N; ++i)
        ans = min(ans, B * d_Bessie[i] + E * d_Elsie[i] + P * d_both[i]);
    cout << ans;
    return 0;
}