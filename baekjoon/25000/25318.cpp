#include <bits/stdc++.h>

constexpr std::array<int, 13> day = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
constexpr std::array<int, 13> day_s = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    if (n == 0) return cout << 0, 0;
    vector<pair<int64_t, int>> a(n);
    char s[11];
    for (auto& [when, score] : a) {
        cin >> s;
        const auto y = atoll(s);
        const auto m = atoll(s + 5);
        auto d = atoll(s + 8) - 1;
        for (int i = 1; i < m; ++i) {
            d += (y == 2020 ? day_s : day)[i];
        }
        if (y > 2020) ++d;
        when = y * 365 + d;
        cin >> s;
        when = when * 24 + stoll(s);
        when = when * 60 + stoll(s + 3);
        when = when * 60 + stoll(s + 6);
        cin >> score;
    }
    constexpr auto year = 1.0 * 365 * 24 * 60 * 60;
    const auto last = a.back().first;
    double x = 0, y = 0;
    for (int i = 0; i < n; ++i) {
        const auto p = max(pow(0.5, (last - a[i].first) / year), pow(0.9, n - i - 1));
        x += p * a[i].second;
        y += p;
    }
    cout << round(x / y);
}
