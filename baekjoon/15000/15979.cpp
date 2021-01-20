#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int x, y;
    cin >> x >> y;
    if (!x && !y)
        cout << 0;
    else
        cout << 1 + (gcd(x, y) != 1);
}