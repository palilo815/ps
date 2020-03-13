#include <iostream>
#include <algorithm>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 100;
const int INF = 1 << 29;

bool frnd[max_N][max_N];
int dist[max_N][max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v; cin >> u >> v;
        --u, --v;
        frnd[u][v] = frnd[v][u] = true;
    }

    loop(i, N) loop(j, N) if (i != j)
        dist[i][j] = frnd[i][j] ? 1 : INF;

    loop(k, N) loop(i, N) loop(j, N)
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    loop(i, N) loop(j, N) if (dist[i][j] > 6) {
        cout << "Big World!";
        return 0;
    }
    cout << "Small World!";
    return 0;
}