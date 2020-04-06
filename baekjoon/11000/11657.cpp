#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;

const int max_N = 500;
const int max_M = 6000;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int edge[max_M][3];
ll dist[max_N + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    loop(i, M) loop(j, 3) cin >> edge[i][j];

    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;

    bool update = false;
    int cnt = N;
    while (cnt--) {
        update = false;
        loop(i, M) {
            auto [u, v, w] = edge[i];
            if (dist[u] != INF && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                update = true;
            }
        }
        if (!update) break;
    }

    if (update) cout << -1;
    else for (int i = 2; i <= N; ++i)
        cout << (dist[i] == INF ? -1 : dist[i]) << '\n';
    return 0;
}