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
    if (--n == 0) return cout << "권병장님, 중대장님이 찾으십니다", 0;
    vector<pair<int, int>> a(n);
    int t;
    for (auto& [x, _] : a) cin >> x;
    cin >> t;
    for (auto& [_, x] : a) cin >> x;
    sort(a.begin(), a.end(), [&](const auto& lhs, const auto& rhs) {
        return lhs.first < rhs.first;
    });
    int x = 0;
    for (const auto& [pos, ran] : a) {
        if (x < pos) break;
        chmax(x, pos + ran);
    }
    cout << (x < t ? "엄마 나 전역 늦어질 것 같아" : "권병장님, 중대장님이 찾으십니다");
}