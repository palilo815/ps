#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

const int mxN = 20;

int mat[mxN][mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;
    loop(i, N) loop(j, N) cin >> mat[i][j];

    int c = (1 << (N >> 1)) - 1, mxN = (1 << N) - 1;
    int ans = INT_MAX;
    while (c <= mxN) {
        int start = 0, link = 0;
        loop(i, N) loop(j, N) {
            int f1 = c & (1 << i), f2 = c & (1 << j);
            if (f1 && f2)
                start += mat[i][j];
            else if (!f1 && !f2)
                link += mat[i][j];
        }

        ans = min(ans, abs(start - link));
        int t = c | (c - 1);
        c = (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(c) + 1));
    }
    cout << ans;
    return 0;
}