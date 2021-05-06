#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    string s;
    cin >> s;

    int c0 = count(s.begin(), s.end(), '0'),
        c1 = s.size() - c0;

    if (c0 != c1)
        cout << string(s.size(), c0 < c1 ? '0' : '1');
    else {
        auto ans = string(s.size(), s[0]);
        ans[0] = '0' + (s[0] == '0');
        cout << ans;
    }
}