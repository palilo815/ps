#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int64_t x;
    cin >> x;
    cout << fixed << setprecision(9)
         << 4 * sqrt(x);
}