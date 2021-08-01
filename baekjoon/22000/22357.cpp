#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr array gaps = {
        1999, 2000, 2001, 2003, 2009, 2011, 2017, 2021, 2027, 2029,
        2033, 2039, 2041, 2053, 2057, 2063, 2069, 2077, 2081, 2083,
        2087, 2089, 2099, 2111, 2113, 2129, 2131, 2137, 2141, 2143};
    int k, n;
    cin >> k >> n;
    for (int i = 0; i < k; ++i) {
        for (int j = 0, x = 1; j < n; ++j, x += gaps[i]) {
            cout << x << ' ';
        }
        cout << '\n';
    }
}