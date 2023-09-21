#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }
    nth_element(a.begin(), a.begin() + n / 2, a.end());
    const auto l = accumulate(a.begin(), a.begin() + n / 2, 0);
    const auto r = accumulate(a.begin() + n / 2, a.end(), 0);
    cout << l << ' ' << r;
}
