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
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    int ans = 0, odd = 0;
    for (auto l = a.begin(), r = l; r != a.end(); ++l) {
        while (r != a.end() && odd + (*r & 1) <= k) {
            odd += *r++ & 1;
        }
        chmax(ans, int(r - l) - odd);
        odd -= *l & 1;
    }
    cout << ans;
}