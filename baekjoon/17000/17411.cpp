#include <bits/stdc++.h>
#define num first
#define cnt second
using namespace std;

const pair<int, int> sentinel = {INT_MAX, 0};
const int mod = 1e9 + 7;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;

    vector<vector<pair<int, int>>> dp(1);
    dp[0] = {sentinel};

    auto psum = [&](vector<pair<int, int>>& vt, int x) {
        int ret = vt.back().cnt - lower_bound(vt.rbegin(), vt.rend(), x, [&](auto& a, auto& b) { return a.num < b; })->cnt;
        return ret >= 0 ? ret : ret + mod;
    };

    for (int x, y; N--;) {
        cin >> x;
        if (x > dp.back().back().num)
            dp.emplace_back(initializer_list<pair<int, int>> {sentinel, {x, psum(dp.back(), x)}});
        else {
            auto it = lower_bound(dp.begin(), dp.end(), x, [&](auto& a, auto& b) { return a.back().num < b; });
            y = *it == dp.front() ? 1 : psum(*prev(it), x);

            if (x == it->back().num)
                it->back().cnt = (it->back().cnt + y) % mod;
            else
                it->emplace_back(x, (y + it->back().cnt) % mod);
        }
    }
    cout << dp.size() << ' ' << dp.back().back().cnt;
}