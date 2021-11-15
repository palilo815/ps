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
    vector<int> a(n), p(k), total(k);
    for (auto& x : a) {
        cin >> x, --x;
        ++total[x];
    }
    int ans = INT_MAX, me = 0, you = k;
    for (auto l = a.begin(), r = l; r != a.end(); ++l) {
        for (; me != k && r != a.end(); ++r) {
            if (++p[*r] == 1) ++me;
            if (p[*r] == total[*r]) --you;
        }
        if (me == k && you == k) chmin(ans, int(r - l));
        if (p[*l] == 1) --me;
        if (p[*l]-- == total[*l]) ++you;
    }
    cout << (ans == INT_MAX ? 0 : ans);
}