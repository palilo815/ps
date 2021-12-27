#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int r, n, m;
    cin >> r >> n >> m, --r;

    map<pair<int, int>, int> dp, nxt;
    dp[{0, 1}] = 1;

    for (int i = n; i--;) {
        nxt.clear();
        for (const auto& [num_kids, x] : dp) {
            if (num_kids.first) {
                const pair nxt_kids(num_kids.first - (i == r), num_kids.second + 1);
                nxt[nxt_kids] = (nxt[nxt_kids] + num_kids.first * int64_t(x)) % m;
            }
            if (num_kids.second) {
                const pair nxt_kids(num_kids.first + (i != r), num_kids.second - 1);
                nxt[nxt_kids] = (nxt[nxt_kids] + num_kids.second * int64_t(x)) % m;
            }
        }
        dp.swap(nxt);
    }

    int ans = 0;
    for (const auto& [_, x] : dp)
        ans = (ans + x) % m;
    cout << ans;
}