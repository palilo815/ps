#include <bits/stdc++.h>
#define loop_1(i, n) for (int i = 1; i <= n; ++i)
using namespace std;

const int mxN = 300;

int psum[mxN + 1][mxN + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;

    loop_1(i, N) loop_1(j, N) cin >> psum[i][j];
    loop_1(i, N) loop_1(j, N)
        psum[i][j] += -psum[i - 1][j - 1] + psum[i - 1][j] + psum[i][j - 1];

    int ans = INT_MIN;
    loop_1(i, N) loop_1(j, N) for (int k = 0; i + k <= N && j + k <= N; ++k)
        ans = max(ans, psum[i + k][j + k] + psum[i - 1][j - 1] - psum[i - 1][j + k] - psum[i + k][j - 1]);
    cout << ans;
    return 0;
}