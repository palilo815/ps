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
    cin >> n >> k;
    vector a = {0}; // sentinel
    int s = 1;
    for (int i = 0, x; i < n - 1; ++i) {
        cin >> x;
        if (x > k) {
            a.emplace_back(s);
            s = 1;
        } else {
            ++s;
        }
    }
    a.emplace_back(s);
    int ans = -1;
    for (int i = 1; i < int(a.size()); ++i) {
        chmax(ans, a[i - 1] + a[i]);
    }
    cout << ans;
}