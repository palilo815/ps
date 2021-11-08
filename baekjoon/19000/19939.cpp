#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;
    const auto sum = [&](int s) {
        return (s + s + k - 1) * k / 2;
    };
    int ans = 0;
    while (sum(ans + 1) <= n) ++ans;
    if (!ans) return cout << -1, 0;
    cout << (k - 1) + !!((n - sum(ans)) % k);
}