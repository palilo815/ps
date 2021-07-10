#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int delta = 710;
    int n;
    cin >> n;
    for (int i = -25000; i < -25000 + n; ++i) {
        cout << delta * i << '\n';
    }
}