#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;
typedef tuple<int, int, int> tup;
typedef long long ll;

const int max_N = 100000;

vector<tup> adj[max_N + 1];
int cost[max_N + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M, K; cin >> N >> M >> K;
    while (M--) {
        int u, v, w1, w2; cin >> u >> v >> w1 >> w2;
        adj[u].emplace_back(w1, w2, v);
        adj[v].emplace_back(w1, w2, u);
    }

    int l = 0, r = 31623, ans = 0;
    while (l <= r) {
        int m = (l + r) / 2;
        memset(cost + 1, 0x3f, sizeof(int) * N);
        cost[1] = 0;

        priority_queue<p, vector<p>, greater<p>> pq;
        pq.emplace(0, 1);

        bool flag = 0;
        while (!pq.empty()) {
            auto [c, u] = pq.top(); pq.pop();
            if (cost[u] < c) continue;
            if (u == N) { flag = 1; break; }

            for (auto [w1, w2, v] : adj[u]) {
                ll C = (m <= w2 ? c : c + ll(w1) * (m - w2) * (m - w2));
                if (C <= K && cost[v] > C) {
                    cost[v] = C;
                    pq.emplace((int)C, v);
                }
            }
        }

        if (flag) {
            ans = m;
            l = m + 1;
        }
        else r = m - 1;
    }
    cout << ans;
    return 0;
}