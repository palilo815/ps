#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e3 + 1;
const int mxM = 1e4 + 1;

vector<pair<int, int>> adj[mxN];
int N, M, K, price[mxM];
bool visited[mxN];

bool solve(int m) {
    memset(visited + 1, 0, N);

    deque<int> dq;
    dq.emplace_back(1);
    dq.emplace_back(0);

    int cnt = K;
    for (;;) {
        int u = dq.front();
        dq.pop_front();
        if (visited[u]) continue;
        if (u == 0) {
            if (cnt-- == 0) return false;
            dq.emplace_back(0);
            continue;
        }
        if (u == N) return true;

        visited[u] = true;
        for (auto& [v, w] : adj[u])
            if (!visited[v])
                w > price[m] ? dq.emplace_back(v) : dq.emplace_front(v);
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> N >> M >> K;
    for (int i = 0, u, v, w; i < M; ++i) {
        cin >> u >> v >> price[i];
        adj[u].emplace_back(v, price[i]);
        adj[v].emplace_back(u, price[i]);
    }

    price[M++] = 0;
    sort(price, price + M);
    M = unique(price, price + M) - price;

    int lo = 0, hi = M;
    while (lo != hi) {
        int m = (lo + hi) >> 1;
        solve(m) ? (hi = m) : (lo = m + 1);
    }
    cout << (lo == M ? -1 : price[lo]);
    return 0;
}