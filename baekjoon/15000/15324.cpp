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
    for (auto& x : a) cin >> x, --x;
    vector<int> pref(n + 1);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + (a[i] == i);
    }
    vector<pair<int, int>> intervals(n);
    for (int i = 0; i < n; ++i) {
        int x = i, y = a[i];
        if (x > y) swap(x, y);
        intervals[i] = {x, y};
    }
    sort(intervals.begin(), intervals.end(), [&](const auto& lhs, const auto& rhs) {
        return lhs.first + lhs.second == rhs.first + rhs.second
                   ? lhs.second < rhs.second
                   : lhs.first + lhs.second < rhs.first + rhs.second;
    });
    int ans = -1, prev_centre = -1, matched_reverse = 0;
    pair best_pos(-1, -1);
    for (const auto& [l, r] : intervals) {
        if (l + r != prev_centre) {
            prev_centre = l + r;
            matched_reverse = 0;
        }
        ++matched_reverse;
        if (chmax(ans, matched_reverse + pref[n] - pref[r + 1] + pref[l])) {
            best_pos = {l, r};
        }
    }
    cout << a[best_pos.first] + 1 << ' ' << a[best_pos.second] + 1;
}