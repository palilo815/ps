#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 500;
const int max_M = 5200;
const int INF = 1 << 29;

int edge[max_M][3];
int dist[max_N + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int N, M, W; cin >> N >> M >> W;
        fill_n(dist + 1, N, INF);

        for (int i = 0; i < 2 * M; i += 2) {
            loop(j, 3) cin >> edge[i][j];
            edge[i + 1][0] = edge[i][1];
            edge[i + 1][1] = edge[i][0];
            edge[i + 1][2] = edge[i][2];
        }

        for (int i = 2 * M; i < 2 * M + W; ++i) {
            cin >> edge[i][0] >> edge[i][1];
            int w; cin >> w;
            edge[i][2] = -w;
        }

        dist[1] = 0;
        M = 2 * M + W;

        bool update = false;
        while (N--) {
            update = false;
            loop(i, M) {
                int u = edge[i][0], v = edge[i][1], w = edge[i][2];
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    update = true;
                }
            }
            if (!update) break;
        }
        if (update) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}