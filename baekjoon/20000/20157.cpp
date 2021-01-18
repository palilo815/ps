#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    unordered_map<uint64_t, int> mp;
    for (int i = 0, x, y; i < n; ++i) {
        cin >> x >> y;
        if (!x)
            ++mp[y > 0 ? 1 : -1];
        else if (!y)
            ++mp[(x > 0 ? 1ll : -1ll) << 32];
        else {
            int g = gcd(x, y);
            x /= g, y /= g;
            ++mp[uint64_t(unsigned(x)) << 32 ^ uint64_t(unsigned(y))];
        }
    }

    cout << max_element(mp.begin(), mp.end(), [&](auto& a, auto& b) {
                return a.second < b.second;
            })->second;
}