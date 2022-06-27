#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    constexpr int CHARS {'r' - 'a' + 1};
    string s, t;
    cin >> s >> t;
    for (auto& x : s) x -= 'a';
    for (auto& x : t) x -= 'a';
    array<int, CHARS> cnt {};
    for (const auto& x : s) ++cnt[x];
    for (const auto& x : t) --cnt[x];
    array<array<bool, CHARS>, CHARS> ok {};
    for (auto i {0}; i < CHARS; ++i) {
        for (auto j {i + 1}; j < CHARS; ++j) {
            if (cnt[i] || cnt[j]) continue;
            auto it {find_if(s.begin(), s.end(), [&](const auto& x) { return x == i || x == j; })};
            auto jt {find_if(t.begin(), t.end(), [&](const auto& x) { return x == i || x == j; })};
            ok[i][j] = true;
            while (it != s.end()) {
                ok[i][j] &= *it == *jt;
                it = find_if(next(it), s.end(), [&](const auto& x) { return x == i || x == j; });
                jt = find_if(next(jt), t.end(), [&](const auto& x) { return x == i || x == j; });
            }
            ok[j][i] = ok[i][j];
        }
    }
    int n;
    cin >> n;
    while (n--) {
        cin >> s;
        auto yes {true};
        yes &= none_of(s.begin(), s.end(), [&](const auto& x) { return cnt[x - 'a']; });
        for (auto i {0}; i < static_cast<int>(s.size()); ++i) {
            for (auto j {i + 1}; j < static_cast<int>(s.size()); ++j) {
                yes &= ok[s[i] - 'a'][s[j] - 'a'];
            }
        }
        cout << (yes ? 'Y' : 'N');
    }
}
