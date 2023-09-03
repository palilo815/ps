#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    auto parse = [] {
        char s[8];
        cin >> s;
        for (auto &x : s) {
            x -= '0';
        }
        const auto year = s[0] * 1000 + s[1] * 100 + s[2] * 10 + s[3] - 2000;
        const auto month = s[5] * 10 + s[6] - 1;
        return year * 12 + month;
    };
    array<int, 12 * 8000> imos{};
    for (auto i = n; i--;) {
        const auto l = parse();
        const auto r = parse() + 1;
        imos[l] += 1;
        imos[r] -= 1;
    }
    for (auto i = static_cast<size_t>(1); i < imos.size(); ++i) {
        imos[i] += imos[i - 1];
    }
    const auto mx = *max_element(imos.begin(), imos.end());
    const auto i = find(imos.begin(), imos.end(), mx) - imos.begin();
    cout << i / 12 + 2000 << '-';
    cout << (i % 12 + 1) / 10 << (i % 12 + 1) % 10;
}
