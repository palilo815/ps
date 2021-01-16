#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    for (int i = 1, x; n--; i ^= 1) {
        cin >> x;
        if (x & 1 != i) return cout << "NO", 0;
    }
    cout << "YES";
}