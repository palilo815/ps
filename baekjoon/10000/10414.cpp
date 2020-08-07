#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;
using p = pair<int, int>;

const int mx = 1001;

vector<p> adj[mx];
int dist[mx];
bool conn[mx], leaf[mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M, K; cin >> N >> M >> K;

    vector<int> insecure(K);
    for (int& x : insecure) cin >> x;
    for (int& x : insecure) leaf[x] = conn[x] = true;

    LOOP(i, M) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    if (N == K) {
        if (N == 1) cout << 0;
        else if (N == 2 && M == 1) cout << adj[1][0].first;
        else cout << "impossible";
        return 0;
    }

    memset(dist, 0x3f, sizeof(int) * (N + 1));
    LOOP(i, N) if (!conn[i]) {
        dist[i] = 0;
        break;
    }

    int ans = 0;
    for (int t = N - K; t--;) {
        int u = 0;
        LOOP(i, N) if (!conn[i] && dist[i] < dist[u])
            u = i;
        if (!u) {cout << "impossible"; return 0;}

        conn[u] = true;
        ans += dist[u];

        for (auto& [w, v] : adj[u])
            if (!conn[v] && dist[v] > w)
                dist[v] = w;
    }

    for (int& u : insecure) {
        int d = INT_MAX;
        for (auto& [w, v] : adj[u])
            if (!leaf[v] && w < d)
                d = w;
        if (d == INT_MAX) {cout << "impossible"; return 0;}
        ans += d;
    }
    cout << ans;
    return 0;
}