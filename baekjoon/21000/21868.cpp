#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int p, q, a, b, x;
    cin >> p >> q >> a >> b >> x;
    cout << (a * x + b) << '\n';
    if (a) {
        cout << p << ' ' << q * abs(a);
    } else {
        cout << "0 0";
    }
}