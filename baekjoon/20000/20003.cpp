#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    ll N, x, y;
    cin >> N >> x >> y;
    ll tmp = gcd(x, y);
    x /= tmp, y /= tmp;

    for (ll a, b, l, g; --N;) {
        cin >> a >> b;

        l = lcm(y, b);
        x *= l / y, a *= l / b;

        x = gcd(x, a);
        y = l;

        g = gcd(x, y);
        x /= g, y /= g;
    }
    cout << x << ' ' << y;
    return 0;
}