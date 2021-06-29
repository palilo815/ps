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

    int ans = 0;
    for (int i = 0, prv_t, prv_d, t, d; i < n; ++i, prv_t = t, prv_d = d) {
        cin >> t >> d;
        if (i) chmax(ans, (d - prv_d) / (t - prv_t));
    }
    cout << ans;
}