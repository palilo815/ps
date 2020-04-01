#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 800;

int N;
int adj[max_N][max_N];
int dist[max_N];

p Dijkstra(int s, int d1, int d2) {
    memset(dist, 0x3f, sizeof(int) * N);
    dist[s] = 0;

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(0, s);

    p ret = { -1,-1 };
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;
        if (u == d1) {
            ret.first = d;
            if (ret.second != -1) break;
        }
        if (u == d2) {
            ret.second = d;
            if (ret.first != -1) break;
        }

        loop(v, N) if (adj[u][v]) {
            int D = d + adj[u][v];
            if (dist[v] > D) {
                dist[v] = D;
                pq.emplace(D, v);
            }
        }
    }
    return ret;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int E; cin >> N >> E;
    while (E--) {
        int u, v, w; cin >> u >> v >> w;
        --u, --v;
        adj[u][v] = adj[v][u] = w;
    }
    int m1, m2; cin >> m1 >> m2;
    --m1, --m2;

    // M = dist( m1 <-> m2 )
    int M = Dijkstra(m1, m1, m2).second;
    if (M == -1) { cout << -1; return 0; }

    // A = dist( 0 -> m1 -> m2 -> N )
    // B = dist( 0 -> m2 -> m1 -> N )
    int A = 0, B = 0;

    // a = dist( 0 -> m1 )
    // b = dist( 0 -> m2 )
    auto [a, b] = Dijkstra(0, m1, m2);
    if (a == -1 || b == -1) { cout << -1; return 0; }
    A += a, B += b;

    // c = dist( N-1 -> m1 )
    // d = dist( N-1 -> m2 )
    auto [c, d] = Dijkstra(N - 1, m1, m2);
    if (c == -1 || d == -1) { cout << -1; return 0; }
    A += d, B += c;

    cout << (min(A, B) + M);
    return 0;
}