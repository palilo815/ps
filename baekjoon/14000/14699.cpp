#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 5000;

p h[max_N + 1];
int DP[max_N + 1];
vector<int> adj[max_N + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    for (int i = 1; i <= N; ++i) {
        cin >> h[i].first;
        h[i].second = i;
    }
    while (M--) {
        int u, v; cin >> u >> v;
        if (h[u].first < h[v].first) swap(u, v);
        adj[u].emplace_back(v);
    }

    sort(h + 1, h + N + 1, greater<p>());
    fill(DP + 1, DP + N + 1, 1);

    for (int i = 1; i <= N; ++i) {
        auto [height, u] = h[i];
        for (int v : adj[u])
            DP[v] = max(DP[v], DP[u] + 1);
    }
    for (int i = 1; i <= N; ++i)
        cout << DP[i] << '\n';
    return 0;
}