#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    auto win = [&](const char& a, const char& b) -> bool {
        switch (a) {
        case 'S': return b == 'P';
        case 'R': return b == 'S';
        case 'P': return b == 'R';
        }
        assert(false);
        return false;
    };
    int n, t;
    string s;
    cin >> n >> t >> s;
    auto cnt = [&]() {
        vector<int> r;
        r.reserve(n);
        auto res = s.begin();
        for (auto it = s.begin(), jt = it; it != s.end(); it = jt) {
            for (++jt; jt != s.end() && *it == *jt; ++jt) {
                ;
            }
            r.emplace_back(jt - it);
            *res++ = *it;
        }
        s.erase(res, s.end());
        return r;
    }();
    assert(s.size() == cnt.size());
    n = s.size();
    for (int i = 0; i < n; ++i) {
        if (i + 1 != n && win(s[i], s[i + 1])) {
            const auto moved = min(t, cnt[i]);
            if (i + 2 != n && s[i] == s[i + 2]) {
                cnt[i] -= moved, cnt[i + 2] += moved;
            } else {
                cout << string(cnt[i] - moved, s[i]) << string(cnt[i + 1], s[i + 1]) << string(moved, s[i]);
                ++i;
                continue;
            }
        }
        cout << string(cnt[i], s[i]);
    }
}