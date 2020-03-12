#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 500;
const int INF = 1 << 29;

int delay[max_N + 1];
int dist[max_N + 1][max_N + 1];
int ans[max_N + 1][max_N + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // ** initialize ** //
    int N, M, Q; cin >> N >> M >> Q;
    LOOP(i, N) cin >> delay[i];
    LOOP(i, N) LOOP(j, N)
        dist[i][j] = (i == j ? 0 : INF);
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        dist[u][v] = w, dist[v][u] = w;
    }
    LOOP(i, N) LOOP(j, N) ans[i][j] = INF;

    // ** 멍멍이가 방해하는 시간이 적은 정점부터 플로이드 ** //
    vector<p> edge;
    LOOP(i, N) edge.emplace_back(delay[i], i);
    sort(edge.begin(), edge.end());

    // delay가 작은 정점부터 고려하므로
    // i -> j로 가는 경로에 포함되는 (i,j는 제외) 모든 정점 x에 대해서
    // delay[x] <= delay[k]
    for (auto [dog, k] : edge) LOOP(i, N) LOOP(j, N) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        ans[i][j] = min(ans[i][j], dist[i][k] + dist[k][j] + max({ dog,delay[i],delay[j] }));
    }
    while (Q--) {
        int src, dst; cin >> src >> dst;
        cout << (ans[src][dst] == INF ? -1 : ans[src][dst]) << '\n';
    }
    return 0;
}