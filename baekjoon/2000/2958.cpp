#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;
typedef tuple<int, int, int> tup;

const int mod = 1000000007;
const int max_N = 1500;
const int max_M = 5000;

vector<tup> adj[max_N + 1];
int dist[max_N];
int ans[max_M];

vector<int> arrive;
int to[max_N], from[max_N];

void Dijkstra(int src, int N) {
    fill(dist, dist + N, INT_MAX);
    dist[src] = 0;
    arrive.clear();

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(0, src);
    to[src] = 1;

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;
        arrive.emplace_back(u);

        for (auto [w, v, i] : adj[u]) {
            int D = d + w;
            if (dist[v] > D) {
                dist[v] = D;
                pq.emplace(D, v);
                to[v] = to[u];
            }
            else if (dist[v] == D)
                to[v] = (to[v] + to[u]) % mod;
        }
    }
}

void calc_path() {
    for (auto it = arrive.rbegin(); it != arrive.rend(); ++it) {
        int u = *it;
        from[u] = 1;
        for (auto [w, v, i] : adj[u])
            if (dist[u] + w == dist[v]) {
                from[u] = (from[u] + from[v]) % mod;
                ans[i] = (ans[i] + (long long)to[u] * from[v]) % mod;
            }
    }
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    loop(i, M) {
        int u, v, w; cin >> u >> v >> w;
        adj[u - 1].emplace_back(w, v - 1, i);
    }

    loop(i, N) {
        Dijkstra(i, N);
        calc_path();
    }
    loop(i, M) cout << ans[i] << '\n';
    return 0;
}