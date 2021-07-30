#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    auto get_int = [&]() -> int {
        string s;
        cin >> s;
        int r = 0;
        for (const auto& x : s) {
            if (x != '.') {
                r = r * 10 + (x - '0');
            }
        }
        return r;
    };
    array<int, 4> a;
    for (auto& x : a) {
        x = get_int();
    }
    sort(a.begin(), a.end());
    const auto t = get_int();
    if (a[0] + a[1] + a[2] > 3 * t) {
        cout << "impossible";
    } else if (a[1] + a[2] + a[3] <= 3 * t) {
        cout << "infinite";
    } else {
        const auto ans = 3 * t - a[1] - a[2];
        cout << ans / 100 << '.' << ans / 10 % 10 << ans % 10;
    }
}