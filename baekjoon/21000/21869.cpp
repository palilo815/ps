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
    if (n == 1) {
        cout << "1\n1 1 ";
    } else {
        cout << (n - 1) * 2 << '\n';
        for (int i = 1; i <= n; ++i) {
            cout << 1 << ' ' << i << '\n';
        }
        for (int i = 2; i <= n - 1; ++i) {
            cout << n << ' ' << i << '\n';
        }
    }
}