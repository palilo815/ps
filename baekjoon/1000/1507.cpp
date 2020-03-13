#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 20;

int road[max_N][max_N];
int dist[max_N][max_N];

int main() {
    int N; cin >> N;
    loop(i, N) loop(j, N) cin >> dist[i][j];
    memcpy(road, dist, sizeof(road));

    loop(k, N) loop(i, N) if (i != k) loop(j, N) if (j != k) {
        if (dist[i][j] > dist[i][k] + dist[k][j]) {
            cout << -1;
            return 0;
        }
        else if (dist[i][j] == dist[i][k] + dist[k][j])
            road[i][j] = 0;
    }

    int ans = 0;
    loop(i, N) loop(j, N)
        ans += road[i][j];
    cout << ans / 2;
    return 0;
}