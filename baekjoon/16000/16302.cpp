#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 1000;

char a[mxN][11];
int d[mxN], par[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, K; cin >> N >> K;
    loop(i, N) cin >> a[i];

    for (int i = 1; i < N; ++i)
        loop(j, K) d[i] += a[0][j] != a[i][j];
    d[0] = INT_MAX;

    int ans = 0;
    loop(_, N - 1) {
        int k = 0;
        for (int i = 1; i < N; ++i)
            if (~d[i] && d[i] < d[k])
                k = i;

        ans += d[k];
        d[k] = -1;

        for (int i = 1; i < N; ++i)
            if (~d[i]) {
                int dist = 0;
                loop(j, K) dist += a[k][j] != a[i][j];
                if (dist < d[i])
                    d[i] = dist, par[i] = k;
            }
    }

    cout << ans;
    for (int i = 1; i < N; ++i)
        cout << '\n' << i << ' ' << par[i];
    return 0;
}