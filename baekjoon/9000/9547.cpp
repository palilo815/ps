#include <bits/stdc++.h>

auto run() {
    using namespace std;
    int c, v;
    cin >> c >> v;
    vector a(v, vector<int>(c));
    for (auto& row : a) {
        for (auto& x : row) {
            cin >> x, --x;
        }
    }
    vector<int> cnt(c);
    for (auto& row : a) {
        ++cnt[row.front()];
    }
    if (auto it {max_element(cnt.begin(), cnt.end())};
        *it > v / 2) {
        cout << (it - cnt.begin()) + 1 << " 1\n";
    } else {
        *it = 0;
        auto jt {max_element(cnt.begin(), cnt.end())};
        const auto i {it - cnt.begin()};
        const auto j {jt - cnt.begin()};
        cout << (count_if(a.begin(), a.end(), [&](const auto& row) {
            return *find_if(row.begin(), row.end(), [&](const auto& x) {
                return x == i || x == j;
            }) == i;
        }) > v / 2
                        ? i + 1
                        : j + 1)
             << " 2\n";
    }
}

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) run();
}
