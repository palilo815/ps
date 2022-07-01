#include <bits/stdc++.h>

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    array<int, 26> cnt {};
    vector<char> ord;
    char s[4];
    for (int i = 0, ed = (n + 2) / 3; i < ed; ++i) {
        cin >> s;
        for (auto ptr = s; *ptr; ++ptr) {
            ++cnt[*ptr - 'A'];
            if (ord.empty() || ord.back() != *ptr) {
                ord.emplace_back(*ptr);
            }
        }
    }
    auto last = ord.begin();
    int acc = 0, best = 0;
    for (auto it = ord.begin(); it != ord.end(); ++it) {
        if (chmax(best, acc + cnt[*it - 'A'])) {
            last = it;
        }
        acc += cnt[*it - 'A'] / 3 * 3;
    }
    for_each(ord.begin(), last, [&](const auto& x) {
        cnt[x - 'A'] = cnt[x - 'A'] / 3 * 3;
    });
    for_each(next(last), ord.end(), [&](const auto& x) {
        cnt[x - 'A'] = 0;
    });
    cout << accumulate(cnt.begin(), cnt.end(), 0) << '\n';
    for (const auto& x : ord) {
        for (int i = 0; i < cnt[x - 'A']; ++i) {
            cout << x;
            if ((i + 1) % 3 == 0) cout << '\n';
        }
    }
}
