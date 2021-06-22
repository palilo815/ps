#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    array<uint64_t, 26> offset;
    offset[0] = 1;
    for (int i = 1; i < 26; ++i)
        offset[i] = offset[i - 1] * 1511ull; // prime

    string s, t;
    cin >> s >> t;

    unordered_set<uint64_t> st;
    for (int len = min(s.size(), t.size()); len; --len) {
        uint64_t h = accumulate(s.begin(), s.begin() + len, 0ull, [&](auto& sum, auto& c) {
            return sum + offset[c - 'a'];
        });

        st.clear();
        st.emplace(h);

        for (int i = len; i < int(s.size()); ++i) {
            h += offset[s[i] - 'a'] - offset[s[i - len] - 'a'];
            st.emplace(h);
        }

        h = accumulate(t.begin(), t.begin() + len, 0ull, [&](auto& sum, auto& c) {
            return sum + offset[c - 'a'];
        });

        if (st.count(h)) return cout << len, 0;
        for (int i = len; i < int(t.size()); ++i) {
            h += offset[t[i] - 'a'] - offset[t[i - len] - 'a'];
            if (st.count(h)) return cout << len, 0;
        }
    }
    cout << 0;
}