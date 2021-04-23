#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k, l;
    cin >> n >> k >> l, l <<= 1;

    // ->  ->  ->  ->    <-
    // bot , ... , top    x
    pair bot {0, 0}, top {0, 0};

    int csum = 0;      // sum of colour of right cameleon
    bool flag = false; // be true when meet the first right cameleon

    vector<int64_t> dp(k), ans(k);

    auto mod = [&](int x) { return x < k ? x : x - k; };

    // p, c = position, colour
    for (int p, c; n--;) {
        char dir;
        cin >> p >> c >> dir, p <<= 1;

        if (dir == 'D') {
            ans[c] += l - p;
            if (flag) {
                rotate(dp.begin(), dp.end() - c, dp.end());
                dp[c] += (p - top.first) >> 1;
            }
            csum = mod(c + csum);
            if (!flag) bot = {p, c}, flag = true;
            top = {p, c};
        } else {
            ans[mod(c + csum)] += (p + bot.first) >> 1;
            ans[c] += (p - top.first) >> 1;
            for (int i = 0; i < k; ++i)
                ans[mod(i + c)] += dp[i];
        }
    }

    for (const auto& x : ans)
        cout << (x >> 1) << '.' << (x & 1 ? 5 : 0) << '\n';
}