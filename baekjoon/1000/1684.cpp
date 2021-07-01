#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, x;
    cin >> n >> x;

    assert(n != 1);

    int res = 0;
    for (int y; --n; x = y) {
        cin >> y;
        res = gcd(res, abs(x - y));
    }
    cout << res;
}