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
    constexpr int MX = 1e5 + 1;
    int n, t;
    cin >> n >> t;
    array<int, MX> pref {};
    for (int k, s, e; n--;) {
        for (cin >> k; k--;) {
            cin >> s >> e;
            ++pref[s], --pref[e];
        }
    }
    partial_sum(pref.begin(), pref.end(), pref.begin());
    auto mx = accumulate(pref.begin(), pref.begin() + t, 0);
    auto cur = mx, st = 0;
    for (int i = 0; i + t < MX; ++i) {
        cur += pref[i + t] - pref[i];
        if (chmax(mx, cur)) {
            st = i + 1;
        }
    }
    cout << st << ' ' << st + t;
}