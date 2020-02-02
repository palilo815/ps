#include <bits/stdc++.h>
using namespace std;
const int max_T = 10000;

int DP[max_T + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // 그냥 냅색문제다.

    int N, T; cin >> N >> T;
    while (N--) {
        int cost, scr; cin >> cost >> scr;
        for (int i = T - cost; i > 0; --i)
            if (DP[i]) DP[i + cost] = max(DP[i + cost], DP[i] + scr);
        DP[cost] = max(DP[cost], scr);
    }

    int ans = 0;
    for (int i = 1; i <= T; ++i)
        ans = max(ans, DP[i]);
    cout << ans;
    return 0;
}