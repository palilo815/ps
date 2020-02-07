#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 500;
const int max_M = 6000;

int edge[max_M][3];
int dist[max_N + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // ** Bellman-Ford **

    int N, M; cin >> N >> M;
    loop(i, M) loop(j, 3) cin >> edge[i][j];

    loop(i, N + 1) dist[i] = INT_MAX;
    dist[1] = 0;

    bool update = false;
    int cnt = N;
    while (cnt--) {
        update = false;
        loop(i, M) {
            int u = edge[i][0], v = edge[i][1], w = edge[i][2];
            if (dist[u] != INT_MAX && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                update = true;
            }
        }
        if (!update) break;
    }

    if (update) cout << -1;
    else for (int i = 2; i <= N; ++i)
        cout << (dist[i] == INT_MAX ? -1 : dist[i]) << '\n';
    return 0;
}