#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
struct elem {
    int d, c, u;
    elem(int d, int c, int u) : d(d), c(c), u(u) {}
    bool operator <(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int mxN = 1e2;
const int mxM = 1e4;

vector<elem> adj[mxN];
int dist[mxN][mxM + 1];

void solve() {
    int N, M, K; cin >> N >> M >> K;

    loop(i, N) adj[i].clear();
    loop(i, N) memset(dist[i], 0x3f, sizeof(int) * (M + 1));
    dist[0][0] = 0;

    for (int u, v, c, d; K--;) {
        cin >> u >> v >> c >> d;
        --u, --v;
        adj[u].emplace_back(d, c, v);
    }

    priority_queue<elem> pq;
    pq.emplace(0, 0, 0);

    int ans = -1;
    while (!pq.empty()) {
        auto [d, c, u] = pq.top(); pq.pop();
        if (dist[u][c] < d) continue;
        if (u == N - 1) {ans = d; break;}

        for (auto& [w1, w2, v] : adj[u]) {
            int D = d + w1, C = c + w2;
            if (C > M || dist[v][C] <= D) continue;

            for (int cost = C; cost <= M && dist[v][cost] > D; ++cost)
                dist[v][cost] = D;
            pq.emplace(D, C, v);
        }
    }

    if (ans == -1) cout << "Poor KCM";
    else cout << ans;
    cout << '\n';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) solve();
    return 0;
}