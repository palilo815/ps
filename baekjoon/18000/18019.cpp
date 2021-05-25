#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

void solve() {
    array<pair<int, int>, 3> a;
    for (auto& [x, y] : a) cin >> x >> y;

    // ㅁㅁㅁ
    int64_t ans = LLONG_MAX;
    for (int i = 0; i < 8; ++i) {
        if (i & 1) swap(a[0].first, a[0].second);
        if (i == 2 || i == 6) swap(a[1].first, a[1].second);
        if (i == 4) swap(a[2].first, a[2].second);

        chmin(ans, (int64_t(a[0].first) + a[1].first + a[2].first) *
                       max({a[0].second, a[1].second, a[2].second}));
    }

    // ㅁ
    // ㅁㅁ
    for (int top = 0; top < 3; ++top) {
        for (int i = 0; i < 8; ++i) {
            if (i & 1) swap(a[0].first, a[0].second);
            if (i == 2 || i == 6) swap(a[1].first, a[1].second);
            if (i == 4) swap(a[2].first, a[2].second);

            int h = 0;
            for (int j = 0; j < 3; ++j)
                if (j != top)
                    chmax(h, a[j].second);

            chmin(ans, int64_t(max(a[top].first, -a[top].first + a[0].first + a[1].first + a[2].first)) *
                           (a[top].second + h));
        }
    }

    cout << ans << '\n';
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) solve();
}