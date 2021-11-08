#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    uint64_t n;
    cin >> n;
    uint64_t ans = 0;
    for (uint64_t p = 1; n; n >>= 1, p *= 3) {
        if (n & 1) ans += p;
    }
    cout << ans;
}