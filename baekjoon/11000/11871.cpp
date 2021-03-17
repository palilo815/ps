#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    int xorsum = 0;
    for (int p; n--;) {
        cin >> p;
        p = p & 1 ? (p + 1) >> 1 : (p >> 1) - 1;
        xorsum ^= p;
    }
    cout << (xorsum ? "koosaga" : "cubelover");
}