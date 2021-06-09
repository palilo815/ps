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

    vector<tuple<int, int, int>> a(n);
    for (auto& [x0, x1, y] : a) {
        cin >> x0 >> x1 >> y;
        if (x0 > x1) swap(x0, x1);
    }

    vector<tuple<int, int, int>> slopes; // oil, dx, dy
    slopes.reserve(n << 1);

    int ans = 0;
    for (const auto& [x, _, y] : a) {
        slopes.clear();
        int oil = 0;
        for (const auto& [lt, rt, y2] : a) {
            if (y == y2) {
                if (lt <= x && x <= rt)
                    oil += rt - lt;
            } else {
                // y2:  lt-----------rt
                // y :         x
                // y2:  lt-----------rt
                if (y2 < y) {
                    slopes.emplace_back(rt - lt, x - rt, y - y2);
                    slopes.emplace_back(lt - rt, x - lt, y - y2);
                } else {
                    slopes.emplace_back(rt - lt, lt - x, y2 - y);
                    slopes.emplace_back(lt - rt, rt - x, y2 - y);
                }
            }
        }

        // dx / dy
        sort(slopes.begin(), slopes.end(), [&](const auto& lhs, const auto& rhs) {
            auto l = int64_t(get<1>(lhs)) * get<2>(rhs);
            auto r = int64_t(get<1>(rhs)) * get<2>(lhs);
            return l == r ? get<0>(lhs) > get<0>(rhs) : l < r;
        });

        chmax(ans, oil);
        for (const auto& [val, _, __] : slopes)
            chmax(ans, oil += val);
    }
    cout << ans;
}