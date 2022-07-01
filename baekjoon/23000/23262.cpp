#include <bits/stdc++.h>

auto run() {
    using namespace std;
    int k;
    cin >> k;
    vector<int> x(k << 1), y(k << 1);
    for (int i = 0; i < k << 1; i += 2) {
        cin >> x[i] >> y[i] >> x[i | 1] >> y[i | 1];
    }
    nth_element(x.begin(), x.begin() + k - 1, x.end());
    nth_element(y.begin(), y.begin() + k - 1, y.end());
    cout << x[k - 1] << ' ' << y[k - 1] << '\n';
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
