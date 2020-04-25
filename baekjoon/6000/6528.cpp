#include <bits/stdc++.h>
using namespace std;
typedef pair<double, int> pdi;

const int max_N = 100;

vector<pdi> adj[max_N + 1];
double probability[max_N + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M;
    while (1) {
        cin >> N;
        if (!N) break;
        cin >> M;
        for (int i = 1; i <= N; ++i) adj[i].clear();
        while (M--) {
            int u, v;
            double w;
            cin >> u >> v >> w;
            adj[u].emplace_back(w, v);
            adj[v].emplace_back(w, u);
        }

        memset(probability, 0, sizeof(double) * (N + 1));
        probability[1] = 100.0;

        priority_queue<pdi> pq;
        pq.emplace(100.0, 1);

        while (1) {
            auto [p, u] = pq.top(); pq.pop();
            if (probability[u] > p) continue;
            if (u == N) break;

            for (auto [w, v] : adj[u]) {
                double P = p * w / 100;
                if (probability[v] < P) {
                    probability[v] = P;
                    pq.emplace(P, v);
                }
            }
        }
        cout << fixed << setprecision(6) << probability[N] << " percent\n";
    }
    return 0;
}