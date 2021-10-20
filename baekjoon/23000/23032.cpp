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
    vector<int> pref(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> pref[i];
    }
    partial_sum(pref.begin(), pref.end(), pref.begin());
    pair best(INT_MIN, 0);
    for (int l = 0; l < n - 1; ++l) {
        for (int m = l + 1, r = m + 1; r != n + 1;) {
            if (m == r) {
                ++r;
                continue;
            }
            const auto lsum = pref[m] - pref[l];
            const auto rsum = pref[r] - pref[m];
            if (lsum < rsum) {
                chmax(best, make_pair(lsum - rsum, lsum + rsum));
                ++m;
            } else {
                chmax(best, make_pair(rsum - lsum, lsum + rsum));
                ++r;
            }
        }
    }
    cout << best.second;
}