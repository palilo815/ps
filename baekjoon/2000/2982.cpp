#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;
typedef tuple<int, int, int, int> tup;

const int max_N = 1000;

vector<tup> adj[max_N + 1];
int dist[max_N + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, src, dst, T, G;
    cin >> N >> M >> src >> dst >> T >> G;

    vector<int> path(G);
    loop(i, G) cin >> path[i];

    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v, 0, 0);
        adj[v].emplace_back(w, u, 0, 0);
    }

    int _time = 0;
    loop(i, G - 1) {
        int s = path[i], e = path[i + 1];
        for (auto& [w, v, t1, t2] : adj[s]) if (v == e) {
            t1 = _time;
            t2 = _time + w;
            break;
        }
        for (auto& [w, v, t1, t2] : adj[e]) if (v == s) {
            t1 = _time;
            t2 = _time + w;
            _time += w;
            break;
        }
    }

    fill(dist + 1, dist + N + 1, INT_MAX);
    dist[src] = T;

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(T, src);
    while (1) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;
        if (u == dst) break;

        for (auto [w, v, t1, t2] : adj[u]) {
            int D = ((t1 <= d && d < t2) ? t2 + w : d + w);
            if (dist[v] > D) {
                dist[v] = D;
                pq.emplace(D, v);
            }
        }
    }
    cout << dist[dst] - T;
    return 0;
}