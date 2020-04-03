#include <bits/stdc++.h>
#define loop(i,n) for(int i=0; i<n; ++i)
using namespace std;

const int max_N = 500;

int x[max_N], y[max_N];
int DP[max_N][max_N];

int dist(int u, int v) {
    return abs(x[u] - x[v]) + abs(y[u] - y[v]);
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, K; cin >> N >> K;
    loop(i, N) cin >> x[i] >> y[i];

    memset(DP, 0x3f, sizeof(DP));
    DP[0][0] = 0;

    loop(e, N) loop(k, e) {
        if (k > K) break;
        for (int s = e - 1; s >= 0 && e - s <= k + 1; --s)
            DP[e][k] = min(DP[e][k], DP[s][k - (e - s - 1)] + dist(s, e));
    }
    cout << DP[N - 1][K];
    return 0;
}