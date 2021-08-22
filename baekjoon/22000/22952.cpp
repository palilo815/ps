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
    cout << n;
    for (int i = 1; i <= n - i; ++i) {
        cout << ' ' << i;
        if (i != n - i) cout << ' ' << n - i;
    }
}