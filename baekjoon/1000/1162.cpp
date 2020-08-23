#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using p = pair<int, int>;
struct elem {
    ll d;
    int u, k;
    elem(ll d, int u, int k) : d(d), u(u), k(k) {}
    bool operator <(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int mxN = 1e4 + 1;
const int mxK = 20;

vector<p> adj[mxN];
ll dist[mxN][mxK + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M, K; cin >> N >> M >> K;
    for (int u, v, w; M--;) {
        cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    memset(dist, 0x3f, sizeof(dist));
    dist[1][0] = 0;

    priority_queue<elem> pq;
    pq.emplace(0, 1, 0);

    while (1) {
        auto [d, u, k] = pq.top(); pq.pop();
        if (u == N) {cout << d; break;}

        for (auto& [w, v] : adj[u]) {
            if (dist[v][k] > d + w) {
                dist[v][k] = d + w;
                pq.emplace(d + w, v, k);
            }
            if (k < K && dist[v][k + 1] > d) {
                dist[v][k + 1] = d;
                pq.emplace(d, v, k + 1);
            }
        }
    }
    return 0;
}