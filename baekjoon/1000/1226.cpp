#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    vector<int> ids(n);
    iota(ids.begin(), ids.end(), 0);
    sort(ids.begin(), ids.end(), [&](auto& l, auto& r) {
        return a[l] > a[r];
    });

    const auto total = accumulate(a.begin(), a.end(), 0),
               half = total >> 1;

    vector<int> dp(total + 1, -1);
    dp[0] = -2;

    for (const auto& id : ids) {
        const auto seat = a[id];
        for (int j = half; ~j; --j)
            if (~dp[j] && dp[j + seat] == -1)
                dp[j + seat] = id;
    }

    const auto mx = dp.rend() - find_if(dp.rbegin(), dp.rend(), [&](auto& x) { return ~x; }) - 1;

    vector<int> ans;
    for (int i = mx; i; i -= a[dp[i]])
        ans.emplace_back(dp[i] + 1);

    cout << ans.size() << '\n';
    for (const auto& x : ans)
        cout << x << ' ';
}