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

    sort(a.begin(), a.end());

    int ans = -1;
    vector<pair<int, int>> stk = {{a[0] + a[1] + a[2] + a[3], a[4]}};
    for (int i = 5; i < n - 1; ++i) {
        while (!stk.empty() && stk.back().first <= stk.back().second + a[i])
            stk.pop_back();

        if (!stk.empty()) {
            if (auto it = lower_bound(a.begin() + i + 1, a.end(), stk.back().second + a[i]);
                it != a.begin() + i + 1)
                ans = max(ans, stk.back().first + stk.back().second + a[i] + *prev(it));
        }
        stk.emplace_back(a[i - 4] + a[i - 3] + a[i - 2] + a[i - 1], a[i]);
    }
    cout << ans;
}