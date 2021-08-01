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
    string s;
    cin >> n >> s;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    auto res = a.begin();
    for (int i = 0, j; i != n; i = j) {
        int mx = a[i];
        for (j = i + 1; j != n && s[i] == s[j]; ++j) {
            chmax(mx, a[j]);
        }
        if (i == 0 || j == n) {
            continue;
        }
        *res++ = mx;
    }
    a.erase(res, a.end());
    sort(a.begin(), a.end(), greater());
    cout << accumulate(a.begin(), a.begin() + (a.size() + 1) / 2, 0ll);
}