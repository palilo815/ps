#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    for (int c, p; n--;) {
        cin >> c >> p;
        cout << c << ' ' << p << '\n'
             << p + (p - 2) * (c - 1) << '\n';
    }
}
