#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int m;
    cin >> m;

    int xorsum = 0;
    for (int p; m--;) {
        cin >> p;
        xorsum ^= p;
    }
    cout << (xorsum ? "koosaga" : "cubelover");
}