#include <bits/stdc++.h>
using namespace std;

const int mxM = 12880;

int dp[mxM + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    for (int w, d; N; --N) {
        cin >> w >> d;
        for (int i = M; i >= w; --i)
            if (dp[i] < dp[i - w] + d)
                dp[i] = dp[i - w] + d;
    }
    cout << dp[M];
    return 0;
}