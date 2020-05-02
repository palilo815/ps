#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;
typedef struct {
    int A, B, C;
    int idx;
} ranking;

const int max_N = 100001;

vector<p> adj[max_N];
int dist[3][max_N];
int tmp_dist[max_N];
ranking hubo[max_N];
bool no[max_N];

int segT[131072 * 2 - 1];

void Dijkstra(int src, int N, int dist[]) {
    memset(dist + 1, 0x3f, sizeof(int) * N);
    dist[src] = 0;

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(0, src);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;

        for (auto [w, v] : adj[u]) {
            int D = d + w;
            if (dist[v] > D) {
                dist[v] = D;
                pq.emplace(D, v);
            }
        }
    }
}
bool cmp(const ranking& x, const ranking& y) { return x.A < y.A; }
void update(int qi, int qv, int l, int r, int idx) {
    segT[idx] = min(segT[idx], qv);
    if (l == r) return;
    int m = l + (r - l) / 2;
    if (qi <= m) update(qi, qv, l, m, 2 * idx + 1);
    else update(qi, qv, m + 1, r, 2 * idx + 2);
}
int query(int ql, int qr, int l, int r, int idx) {
    if (ql <= l && r <= qr) return segT[idx];
    if (qr < l || r < ql) return INT_MAX;
    int m = l + (r - l) / 2;
    return min(query(ql, qr, l, m, 2 * idx + 1), query(ql, qr, m + 1, r, 2 * idx + 2));
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, A, B, C, M;
    cin >> N >> A >> B >> C >> M;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    Dijkstra(A, N, dist[0]);
    Dijkstra(B, N, dist[1]);
    Dijkstra(C, N, dist[2]);

    loop(i, N) hubo[i].idx = i + 1;

    memcpy(tmp_dist, dist[0] + 1, sizeof(int) * N);
    sort(tmp_dist, tmp_dist + N);
    loop(i, N) hubo[i].A = lower_bound(tmp_dist, tmp_dist + N, dist[0][i + 1]) - tmp_dist;

    memcpy(tmp_dist, dist[1] + 1, sizeof(int) * N);
    sort(tmp_dist, tmp_dist + N);
    loop(i, N) hubo[i].B = lower_bound(tmp_dist, tmp_dist + N, dist[1][i + 1]) - tmp_dist;

    memcpy(tmp_dist, dist[2] + 1, sizeof(int) * N);
    sort(tmp_dist, tmp_dist + N);
    loop(i, N) hubo[i].C = lower_bound(tmp_dist, tmp_dist + N, dist[2][i + 1]) - tmp_dist;
    
    memset(segT, 0x3f, sizeof(segT));
    sort(hubo, hubo + N, cmp);

    loop(i, N) {
        int j = i;
        while (j + 1 < N && hubo[j + 1].A == hubo[i].A) ++j;

        for (int k = i; k <= j; ++k) {
            int q = query(0, hubo[k].B - 1, 0, N - 1, 0);
            if (q < hubo[k].C) no[hubo[k].idx] = true;
        }
        for (int k = i; k <= j; ++k)
            update(hubo[k].B, hubo[k].C, 0, N - 1, 0);
        i = j;
    }

    int Q; cin >> Q;
    while (Q--) {
        int idx; cin >> idx;
        cout << (no[idx] ? "NO" : "YES") << '\n';
    }
    return 0;
}