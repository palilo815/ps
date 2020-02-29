#include <bits/stdc++.h>
using namespace std;

const int max_N = 10000;

int DP[max_N + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    memset(DP, -1, sizeof(DP));
    DP[0] = 0;
    int N, K; cin >> N >> K;
    while (K--) {
        int val, cost; cin >> val >> cost;
        for (int t = N - cost; t >= 0; --t) if (DP[t] != -1)
            DP[t + cost] = max(DP[t + cost], DP[t] + val);
    }

    int ans = 0;
    for (int t = 0;t <= N; ++t) ans = max(ans, DP[t]);
    cout << ans;
    return 0;
}