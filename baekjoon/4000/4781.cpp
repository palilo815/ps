#include <bits/stdc++.h>
using namespace std;

const int mxN = 5e3;
const int mxM = 1e4;

int c[mxN], p[mxN], dp[mxM + 1];
char s[7];

int read_int() {
    int ret = 0;
    for (int i = 0; s[i]; ++i) {
        if (s[i] == '.') continue;
        ret = ret * 10 + s[i] - '0';
    }
    return ret;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int N, M;
    for (;;) {
        cin >> N >> s;
        if (!N) break;
        M = read_int();

        for (int i = 0; i < N; ++i) {
            cin >> c[i] >> s;
            p[i] = read_int();
        }

        memset(dp + 1, -1, sizeof(int) * M);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j <= M - p[i]; ++j)
                if (~dp[j])
                    dp[j + p[i]] = max(dp[j + p[i]], dp[j] + c[i]);
        cout << *max_element(dp, dp + M + 1) << '\n';
    }
    return 0;
}