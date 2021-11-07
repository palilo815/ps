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
    int sa, sb, sc, n;
    cin >> sa >> sb >> sc >> n;
    int ans = -1;
    for (int res; n--;) {
        res = 0;
        for (int i = 3, a, b, c; i--;) {
            cin >> a >> b >> c;
            res += a * sa + b * sb + c * sc;
        }
        chmax(ans, res);
    }
    cout << ans;
}