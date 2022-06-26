#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector dp(n, INT_MAX);
    for (int x; n--;) {
        cin >> x;
        *lower_bound(dp.begin(), dp.end(), x) = x;
    }
    cout << find(dp.begin(), dp.end(), INT_MAX) - dp.begin();
}
