#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int r, g, b;
    cin >> r >> g >> b;
    int ans = 0;
    ans += r / 3, r %= 3;
    ans += g / 3, g %= 3;
    ans += b / 3, b %= 3;
    const auto x = !!r + !!g + !!b;
    if (x) ++ans;
    if (x > 1) ans += (r > 1) || (g > 1) || (b > 1);
    cout << ans;
}