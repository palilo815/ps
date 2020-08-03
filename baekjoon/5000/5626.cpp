#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define sum(i) (((prv[i - 1] + prv[i]) % mod + prv[i + 1]) % mod)
using namespace std;

const int mx = 1e4;
const int mod = 1e9 + 7;

int a[mx], dp[2][mx >> 1 | 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> a[i];
    loop(i, N) ++a[i];

    if (a[0] > 1 || a[N - 1] > 1) {
        cout << 0;
        return 0;
    }
    a[0] = a[N - 1] = 1;

    int* prv = dp[0], * cur = dp[1];
    cur[1] = 1;
    loop(i, N) {
        swap(prv, cur);
        int M = min(i + 1, N - i);
        memset(cur + 1, 0, sizeof(int) * M);

        if (a[i]) cur[a[i]] = sum(a[i]);
        else for (int j = 1; j <= M; ++j) cur[j] = sum(j);
    }
    cout << cur[1];
    return 0;
}