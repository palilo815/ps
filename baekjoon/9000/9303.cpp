#include <bits/stdc++.h>
using namespace std;
typedef pair<double, int> pdi;

const int max_N = 100;

vector<pdi> adj[max_N + 1];
double probability[max_N + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        int N, M, src, dst;
        cin >> N >> src >> dst >> M;
        
        for (int i = 1; i <= N; ++i) adj[i].clear();
        memset(probability, 0, sizeof(double) * (N + 1));
        probability[src] = 1.0;

        while (M--) {
            int u, v;
            double w;
            cin >> u >> v >> w;
            adj[u].emplace_back(w, v);
        }

        priority_queue<pdi> pq;
        pq.emplace(1.0, src);

        while (1) {
            auto [p, u] = pq.top(); pq.pop();
            if (probability[u] > p) continue;
            if (u == dst) break;

            for (auto [w, v] : adj[u]) {
                double P = p * w;
                if (probability[v] < P) {
                    probability[v] = P;
                    pq.emplace(P, v);
                }
            }
        }
        cout << "Case " << t << ": "
             << fixed << setprecision(6) << probability[dst] << '\n';
    }
    return 0;
}