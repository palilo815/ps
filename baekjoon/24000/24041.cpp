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
    int n, g, k;
    cin >> n >> g >> k;
    struct food {
        int s, l, o;
    };
    vector<food> a(n);
    for (auto& [s, l, o] : a) {
        cin >> s >> l >> o;
    }
    const auto m = partition(a.begin(), a.end(), [&](const auto& x) {
        return x.o;
    }) - a.begin();
    chmin(k, int(m));
    vector<int64_t> cnt(n);
    constexpr int64_t INF = 0x3f3f3f3f;
    auto parametric = [&](auto lo, auto hi) {
        auto f = [&](auto mid) -> bool {
            transform(a.begin(), a.end(), cnt.begin(), [&](const auto& x) {
                const int64_t y = max(int64_t(1), mid - x.l);
                return min(y * x.s, INF);
            });
            nth_element(cnt.begin(), cnt.begin() + k, cnt.begin() + m, greater());
            return accumulate(cnt.begin() + k, cnt.end(), int64_t(0)) <= g;
        };
        // last true
        while (lo != hi) {
            auto mid = hi - (hi - lo) / 2;
            f(mid) ? lo = mid : hi = mid - 1;
        }
        return lo;
    };
    cout << parametric(int64_t(0), int64_t(2e9));
}
