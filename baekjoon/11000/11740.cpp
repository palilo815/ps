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
    int w, n;
    cin >> w >> n;
    if (n == 0) return cout << w / 2 << '.' << (w & 1 ? 5 : 0) << ' ' << 0, 0;
    vector<pair<int, int>> a(n);
    for (auto& [x, y] : a) {
        cin >> x >> y;
    }
    const auto dist2 = [&](const pair<int, int>& u, const pair<int, int>& v) {
        const int64_t dx = u.first - v.first;
        const int64_t dy = u.second - v.second;
        return dx * dx + dy * dy;
    };
    const auto dijk = [&](vector<int64_t>& d) {
        vector<bool> visited(n);
        for (int i = 0; i < n; ++i) {
            int k = -1;
            for (int j = 0; j < n; ++j) {
                if (!visited[j] && (k == -1 || d[j] < d[k])) {
                    k = j;
                }
            }
            visited[k] = true;
            for (int j = 0; j < n; ++j) {
                chmin(d[j], max(d[k], dist2(a[j], a[k])));
            }
        }
    };
    vector<int64_t> dl(n);
    transform(a.begin(), a.end(), dl.begin(), [&](const auto& x) {
        return int64_t(x.first) * x.first;
    });
    dijk(dl);
    vector<int64_t> dr(n);
    transform(a.begin(), a.end(), dr.begin(), [&](const auto& x) {
        return int64_t(w - x.first) * (w - x.first);
    });
    dijk(dr);
    int64_t ans = LLONG_MAX;
    pair stone(-1, -1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (chmin(ans, max(dist2(a[i], a[j]), 4 * max(dl[i], dr[j])))) {
                stone = {a[i].first + a[j].first, a[i].second + a[j].second};
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (chmin(ans, max(int64_t(w - a[i].first) * (w - a[i].first), 4 * dl[i]))) {
            stone = {a[i].first + w, a[i].second << 1};
        }
        if (chmin(ans, max(int64_t(a[i].first) * a[i].first, 4 * dr[i]))) {
            stone = {a[i].first, a[i].second << 1};
        }
    }
    cout << stone.first / 2 << '.' << (stone.first & 1 ? 5 : 0) << ' ';
    cout << stone.second / 2 << '.' << (stone.second & 1 ? 5 : 0) << ' ';
}