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
    for (int x; n--;) {
        cin >> x;
        if (x % 4 == 0)
            --x;
        else if (x % 4 == 3)
            ++x;
        xorsum ^= x;
    }
    cout << (xorsum ? "koosaga" : "cubelover");
}