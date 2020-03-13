#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 300;
const int INF = 1 << 29;

p line[max_N];
int dist[max_N][max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> line[i].first >> line[i].second;

    loop(i, N) loop(j, N) if (i != j)
        dist[i][j] = ((line[i].first > line[j].second || line[i].second < line[j].first) ? INF : 1);

    loop(k, N) loop(i, N) loop(j, N)
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    int Q; cin >> Q;
    while (Q--) {
        int u, v; cin >> u >> v;
        --u, --v;
        cout << (dist[u][v] == INF ? -1 : dist[u][v]) << '\n';
    }
    return 0;
}