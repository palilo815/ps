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
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    vector<int64_t> pref(n), suff(n);
    for (int i = 1; i < n; ++i) cin >> pref[i];
    for (int i = 0; i < n - 1; ++i) cin >> suff[i];
    partial_sum(pref.begin(), pref.end(), pref.begin());
    partial_sum(suff.rbegin(), suff.rend(), suff.rbegin());
    pair ans(LLONG_MAX, INT_MAX);
    for (int i = 0; i < n; ++i) {
        chmin(ans, pair(a[i] + pref[i] + suff[i], i));
    }
    cout << ans.second + 1 << ' ' << ans.first;
}