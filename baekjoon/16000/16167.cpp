#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 101;

vector<p> adj[max_N];
int cost[max_N];
int cnt[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v, w1, w2, d;
        cin >> u >> v >> w1 >> w2 >> d;
        int w = w1 + ((d > 10) ? ((d - 10) * w2) : 0);
        adj[u].emplace_back(w, v);
    }

    memset(cost + 1, 0x3f, sizeof(int) * N);
    memset(cnt + 1, 0x3f, sizeof(int) * N);

    cost[1] = 0;
    cnt[1] = 1;

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(0, 1);

    int flag = 0;
    while (!pq.empty()) {
        auto [c, u] = pq.top(); pq.pop();
        if (cost[u] < c) continue;
        if (u == N) { flag = 1; break; }

        for (auto [w, v] : adj[u]) {
            int C = c + w;
            if (C < cost[v]) {
                cost[v] = C;
                cnt[v] = cnt[u] + 1;
                pq.emplace(C, v);
            }
            else if (C == cost[v])
                cnt[v] = min(cnt[v], cnt[u] + 1);
        }
    }

    if (flag) cout << cost[N] << ' ' << cnt[N];
    else cout << "It is not a great way.";
    return 0;
}