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

    string s;
    cin >> s;

    string ans = "~";
    for (int i = 1; i < int(s.size()) - 1; ++i)
        for (int j = i + 1; j < int(s.size()); ++j) {
            string t = s;
            reverse(t.begin(), t.begin() + i);
            reverse(t.begin() + i, t.begin() + j);
            reverse(t.begin() + j, t.end());
            chmin(ans, t);
        }
    cout << ans;
}