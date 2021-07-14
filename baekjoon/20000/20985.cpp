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
    int n, q;
    cin >> n >> q;
    vector<int64_t> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    vector<pair<int64_t, int>> intervals(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        intervals[i] = {a[i + 1] - a[i], i};
    }
    sort(intervals.begin(), intervals.end(), [&](const auto& lhs, const auto& rhs) {
        return lhs.first < rhs.first;
    });
    int ptr = 0;
    int64_t lmax = 0, rmax = 0;
    vector<int64_t> ans(n);
    for (int64_t w, psum = 0; q--;) {
        cin >> w;
        psum += w;
        if (psum < 0) {
            for (chmin(lmax, psum); ptr != n - 1 && intervals[ptr].first <= rmax - lmax; ++ptr) {
                ans[intervals[ptr].second] += rmax;
                ans[intervals[ptr].second + 1] += intervals[ptr].first - rmax;
            }
        } else {
            for (chmax(rmax, psum); ptr != n - 1 && intervals[ptr].first <= rmax - lmax; ++ptr) {
                ans[intervals[ptr].second + 1] -= lmax;
                ans[intervals[ptr].second] += intervals[ptr].first + lmax;
            }
        }
    }
    ans.front() -= lmax;
    ans.back() += rmax;
    for (; ptr != n - 1; ++ptr) {
        ans[intervals[ptr].second] += rmax;
        ans[intervals[ptr].second + 1] -= lmax;
    }
    for (const auto& x : ans) {
        cout << x << '\n';
    }
}