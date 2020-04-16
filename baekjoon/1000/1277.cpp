#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<double, int> p;

const int max_N = 1000;

int x[max_N], y[max_N];
double adj[max_N][max_N];
double dist[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, W; cin >> N >> W;
    double M; cin >> M;
    M += 1e-6;

    loop(i, N) cin >> x[i] >> y[i];
    loop(j, N) loop(i, j) {
        long long dx = x[i] - x[j], dy = y[i] - y[j];
        adj[i][j] = adj[j][i] = sqrt(dx * dx + dy * dy);
    }
    while (W--) {
        int u, v; cin >> u >> v;
        --u, --v;
        adj[u][v] = adj[v][u] = 0;
    }

    fill(dist + 1, dist + N, DBL_MAX);

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(0, 0);

    int ans = -1;
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;
        if (u == N - 1) { ans = d * 1000; break; }

        loop(v, N) if (adj[u][v] <= M) {
            double D = d + adj[u][v];
            if (dist[v] > D) {
                dist[v] = D;
                pq.emplace(D, v);
            }
        }
    }
    cout << ans;
    return 0;
}