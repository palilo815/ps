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
    constexpr int MAX = 1e8;
    int n;
    cin >> n;
    vector<tuple<int, int, int>> a(n);
    for (auto& [x, y, h] : a) {
        cin >> x >> y >> h;
    }
    auto fx = [&](auto pos) -> int {
        int ret = 0;
        for (const auto& [x, _, h] : a) {
            chmax(ret, h + abs(pos - x));
        }
        return ret;
    };
    auto fy = [&](auto pos) -> int {
        int ret = 0;
        for (const auto& [_, y, h] : a) {
            chmax(ret, h + abs(pos - y));
        }
        return ret;
    };
    auto ternary = [&](auto lo, auto hi, auto f) {
        while (lo != hi) {
            auto mid = lo + (hi - lo) / 2;
            f(mid) <= f(mid + 1) ? hi = mid : lo = mid + 1;
        }
        return lo;
    };
    const int x = ternary(-MAX, MAX + 1, fx);
    const int y = ternary(-MAX, MAX + 1, fy);
    cout << x << ' ' << y << ' ' << max(fx(x), fy(y));
}