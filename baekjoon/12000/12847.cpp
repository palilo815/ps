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
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    auto ans = accumulate(a.begin(), a.begin() + m, 0LL), cur = ans;
    for (int i = 0; i + m < n; ++i) {
        cur += a[i + m] - a[i];
        chmax(ans, cur);
    }
    cout << ans;
}