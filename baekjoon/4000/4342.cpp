#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    for (int64_t n, m;;) {
        cin >> n >> m;
        if (!n) break;
        if (n < m) swap(n, m);
        int flag = 0;
        for (;;) {
            if (n % m == 0 || n > 2 * m) break;
            n = exchange(m, n % m), flag ^= 1;
        }
        cout << (flag ? 'B' : 'A') << " wins\n";
    }
}