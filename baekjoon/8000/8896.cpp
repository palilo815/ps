#include <bits/stdc++.h>

auto run() {
    using namespace std;
    int n;
    cin >> n;
    vector<pair<string, int>> robots(n);
    for (int i {}; i < n; ++i) {
        cin >> robots[i].first;
        transform(robots[i].first.begin(), robots[i].first.end(), robots[i].first.begin(), [&](const auto& x) {
            if (x == 'R') return 0;
            if (x == 'S') return 1;
            return 2;
        });
        robots[i].second = i + 1;
    }
    array<int, 3> cnt;
    for (size_t i {0}; i < robots[0].first.size() && robots.size() != 1; ++i) {
        cnt.fill(0);
        for (const auto& [s, _] : robots) {
            ++cnt[s[i]];
        }
        if (!!cnt[0] + !!cnt[1] + !!cnt[2] != 2) continue;
        const auto loser {[&]() {
            if (!cnt[0]) return 2;
            if (!cnt[1]) return 0;
            return 1;
        }()};
        robots.erase(remove_if(robots.begin(), robots.end(), [&](const auto& s) {
            return s.first[i] == loser;
        }),
            robots.end());
    }
    if (robots.size() == 1) {
        cout << robots[0].second << '\n';
    } else {
        cout << 0 << '\n';
    }
}

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) run();
}
