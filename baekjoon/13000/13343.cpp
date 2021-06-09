#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    constexpr array res = {"lose", "win"};

    int64_t n, m;
    cin >> n >> m;

    if (n < m) swap(n, m);

    for (bool me = true;; me ^= true) {
        if (n % m == 0 || n > 2 * m)
            return cout << res[me], 0;
        n = exchange(m, n % m);
    }
}