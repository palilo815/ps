#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    auto const pivot = min_element(a.begin(), a.end());
    rotate(a.begin(), pivot, a.end());
    auto ans = 1;
    for (auto i = 1; i < n; ++i) {
        ans += a[i - 1] >= a[i];
    }
    cout << ans;
}
