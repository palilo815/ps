#include <bits/stdc++.h>

auto run() {
    using namespace std;
    int n, a;
    cin >> n >> a;
    if (a < n - 2) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    cout << "POSSIBLE\n";
    vector<pair<int, int>> l, r;
    l.reserve(n >> 1), r.reserve(n >> 1);
    int x = 0, y = 0;
    for (; n > 2; n -= 2, x ^= 1, ++y, a -= 2) {
        l.emplace_back(x, y);
        r.emplace_back(x + 1, y);
    }
    if (n == 1) {
        cout << 1 << ' ' << y + a + 1 << '\n';
        reverse(l.begin(), l.end());
    } else {
        cout << 1 << ' ' << y << '\n';
        cout << (x == 0 ? 2 : 0) << ' ' << y + a << '\n';
        if (x == 0) {
            reverse(r.begin(), r.end());
            l.swap(r);
        } else {
            reverse(l.begin(), l.end());
        }
    }
    for (const auto& [x, y] : l) {
        cout << x << ' ' << y << '\n';
    }
    for (const auto& [x, y] : r) {
        cout << x << ' ' << y << '\n';
    }
}

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; ++tc) {
        cout << "Case #" << tc << ": ";
        run();
    }
}
