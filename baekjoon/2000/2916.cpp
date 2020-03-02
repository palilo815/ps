#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, Q; cin >> N >> Q;
    int g; cin >> g;
    g = gcd(360, g);
    while (--N) {
        int x; cin >> x;
        g = gcd(g, x);
    }
    while (Q--) {
        int q; cin >> q;
        cout << (q % g ? "NO" : "YES") << '\n';
    }
    return 0;
}