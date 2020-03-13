#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 100;

bool adj[max_N][max_N];
bool rev[max_N][max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v; cin >> u >> v;
        --u, --v;
        adj[u][v] = true;
        rev[v][u] = true;
    }
    loop(i, N) adj[i][i] = rev[i][i] = true;

    loop(k, N) loop(i, N) loop(j, N) {
        adj[i][j] = adj[i][j] || (adj[i][k] && adj[k][j]);
        rev[i][j] = rev[i][j] || (rev[i][k] && rev[k][j]);
    }

    int ans = N;
    loop(i, N) loop(j, N)
        if (!adj[i][j] && !rev[i][j]) {
            --ans;
            break;
        }
    cout << ans;
    return 0;
}
