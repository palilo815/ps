#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 1e3;

int adj[mxN][mxN], dist[mxN];
bool conn[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) loop(j, N) cin >> adj[i][j];
    loop(i, N) cin >> dist[i];

    int ans = 0;
    loop(_, N) {
        int k = -1;
        loop(i, N) if (!conn[i] && (k == -1 || dist[i] < dist[k]))
            k = i;

        ans += dist[k];
        conn[k] = true;

        loop(i, N) if (!conn[i] && adj[k][i] < dist[i])
            dist[i] = adj[k][i];
    }
    cout << ans;
    return 0;
}