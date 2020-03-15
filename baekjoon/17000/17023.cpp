#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;
typedef pair<int, int> p;
typedef long long ll;

const int max_N = 10000;

int cow[max_N + 1];
int parent[max_N + 1];
p dist[max_N + 1];
vector<p> adj[max_N + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, T; cin >> N >> M >> T;
    LOOP(i,N) cin >> cow[i];
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    LOOP(i,N) dist[i] = { INT_MAX,i };
    dist[1].first = 0;

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(0, 1);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u].first < d) continue;

        for (auto [w, v] : adj[u]) {
            int D = d + w;
            if (dist[v].first > D) {
                dist[v].first = D;
                parent[v] = u;
                pq.emplace(D, v);
            }
            if (dist[v].first == D)
                parent[v] = min(parent[v], u);
        }
    }

    sort(dist + 1, dist + N + 1, greater<p>());
    ll ans = 0;
    LOOP(i, N) {
        auto [d, u] = dist[i];
        int c = cow[u];
        ans = max(ans, ll(d - T) * c);
        cow[parent[u]] += c;
    }
    cout << ans;
    return 0;
}