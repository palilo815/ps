#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    auto sz = 1 << (__lg(n - 1) + 1);
    cout << sz << ' ';
    int ans = 0;
    for (;;) {
        if (n & sz) n ^= sz;
        if (n == 0) break;
        sz >>= 1, ++ans;
    }
    cout << ans;
}