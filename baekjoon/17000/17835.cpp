#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;

const int max_N = 100000;

vector<pii> rev[max_N + 1];
ll dist[max_N + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int V, E, K; cin >> V >> E >> K;
    while (E--) {
        int u, v, w; cin >> u >> v >> w;
        rev[v].emplace_back(w, u);
    }

    memset(dist, 0x3f, sizeof(dist));
    priority_queue <pli, vector<pli>, greater<pli>> pq;

    while (K--) {
        int x; cin >> x;
        pq.emplace(0, x);
        dist[x] = 0;
    }

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;

        for (auto [w, v] : rev[u]) {
            ll D = d + w;
            if (dist[v] > D) {
                dist[v] = D;
                pq.emplace(D, v);
            }
        }
    }

    auto ans = max_element(dist + 1, dist + V + 1);
    cout << ans - dist << '\n' << *ans;
    return 0;
}