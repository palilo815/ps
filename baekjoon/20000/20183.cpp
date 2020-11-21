#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

struct elem {
    int64_t d;
    int u;
    elem(int64_t d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

vector<pair<int, int>> adj[mxN + 1];
int64_t dist[mxN + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M, A, B;
    int64_t C;
    cin >> N >> M >> A >> B >> C;

    for (int u, v, w; M--;) {
        cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    const int mx = 1e9;

    int lo = 0, hi = mx + 1;
    while (lo != hi) {
        int m = (lo + hi) >> 1;
        auto valid = [&]() {
            memset(dist + 1, 0x3f, sizeof(int64_t) * N);

            priority_queue<elem> pq;
            pq.emplace(dist[A] = 0, A);

            while (!pq.empty()) {
                auto [d, u] = pq.top();
                pq.pop();
                if (u == B) return true;
                if (d != dist[u]) continue;

                for (auto& [w, v] : adj[u])
                    if (m >= w && C >= d + w && dist[v] > d + w)
                        pq.emplace(dist[v] = d + w, v);
            }
            return false;
        };
        valid() ? hi = m : lo = m + 1;
    }
    cout << (lo == mx + 1 ? -1 : lo);
}