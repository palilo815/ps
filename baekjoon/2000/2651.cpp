#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e2;

unsigned psum[mxN + 2], t[mxN + 1], dp[mxN + 2], prv[mxN + 2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int mov, n;
    cin >> mov >> n;

    for (int i = 1; i <= n + 1; ++i)
        cin >> psum[i];
    partial_sum(psum + 1, psum + n + 2, psum + 1);

    for (int i = 1; i <= n; ++i)
        cin >> t[i];

    memset(dp + 1, 0xff, sizeof(int) * (n + 1));
    for (int st = 0; st <= n; ++st) {
        int ed = upper_bound(psum + st + 1, psum + n + 2, psum[st] + mov) - psum;
        for (int i = st + 1; i < ed; ++i)
            if (dp[i] > dp[st] + t[st])
                dp[i] = dp[st] + t[st], prv[i] = st;
    }

    vector<int> path;
    for (int u = prv[n + 1]; u; u = prv[u])
        path.emplace_back(u);
    reverse(path.begin(), path.end());

    cout << dp[n + 1] << '\n'
         << path.size() << '\n';
    for (auto& x : path) cout << x << ' ';
}