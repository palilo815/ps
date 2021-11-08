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
    int n, k;
    cin >> n >> k, k <<= 1;
    vector<pair<int, int>> a(n);
    for (auto& [x, y] : a) {
        cin >> x >> y;
    }
    sort(a.begin(), a.end(), [&](const auto& lhs, const auto& rhs) {
        return lhs.second < rhs.second;
    });
    int ans = 0, ice = 0;
    for (auto l = a.begin(), r = l; r != a.end(); ++l) {
        for (; r != a.end() && r->second <= l->second + k; ++r) {
            ice += r->first;
        }
        chmax(ans, ice);
        ice -= l->first;
    }
    cout << ans;
}