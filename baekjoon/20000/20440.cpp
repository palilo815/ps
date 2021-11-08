#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<int> s(n), t(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i] >> t[i];
    }
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    int ans = 0, cur = 0, prv_time = 0;
    pair<int, int> interval;
    auto l = s.begin(), r = t.begin();
    while (l != s.end()) {
        if (*l == *r) {
            ++l, ++r;
        } else if (*l < *r) {
            ++cur;
            prv_time = *l;
            ++l;
        } else {
            if (chmax(ans, cur--)) {
                interval = {prv_time, *r};
            }
            ++r;
        }
    }
    if (chmax(ans, cur--)) interval = {prv_time, *r};
    cout << ans << '\n'
         << interval.first << ' ' << interval.second;
}