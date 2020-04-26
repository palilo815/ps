#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 100;
const int INF = 0x3f3f3f3f;

int adj[max_N][max_N];
int dist[max_N];
bool conn[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int total = 0;
    int N; cin >> N;
    loop(i, N) loop(j, N) {
        char c; cin >> c;
        if (c == '0') adj[i][j] = INF;
        else {
            if (c <= 'Z') adj[i][j] = c - 'A' + 27;
            else adj[i][j] = c - 'a' + 1;
            total += adj[i][j];
        }
    }

    memset(dist, 0x3f, sizeof(int) * N);
    dist[0] = 0;

    int cnt = N, MST = 0;
    while (cnt--) {
        int k = -1;
        loop(i, N) if (!conn[i] && (k == -1 || dist[i] < dist[k]))
            k = i;

        if (dist[k] == INF) { cout << -1; return 0; }
        conn[k] = true;
        MST += dist[k];

        loop(i, N) if (!conn[i])
            dist[i] = min({ dist[i], adj[k][i], adj[i][k] });
    }
    cout << total - MST;
    return 0;
}