#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int ans = 0;
    for (int x, i = 6; i--;) {
        cin >> x;
        ans += x;
    }
    cout << ans * 5;
}
