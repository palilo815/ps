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
    int s;
    cin >> s >> n;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    array<int, 8> d;
    auto bio_diff = [&](int v) {
        for (int u = s, i = 8; i--; u /= 10, v /= 10) {
            d[i] = abs(u % 10 - v % 10);
        }
        return (d[0] * d[0] + d[1] * d[1] + d[2] * d[2] + d[3] * d[3]) *
               (d[4] * d[4] + d[5] * d[5]) *
               (d[6] * d[6] + d[7] * d[7]);
    };
    int mx = -1, ans = 0;
    for (const auto& x : a) {
        if (chmax(mx, bio_diff(x))) {
            ans = x;
        }
    }
    cout << ans;
}