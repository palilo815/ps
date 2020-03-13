#include <iostream>
#include <algorithm>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 500;

int dist[max_N][max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    loop(i, N) loop(j, N) cin >> dist[i][j];

    loop(k, N) loop(i, N) loop(j, N)
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    while (M--) {
        int u, v, t; cin >> u >> v >> t;
        cout << (dist[u - 1][v - 1] <= t ? "Enjoy other party" : "Stay here") << '\n';
    }
    return 0;
}