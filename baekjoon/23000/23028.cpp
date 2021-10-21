#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, a, b;
    cin >> n >> a >> b;
    for (int i = 8 - n, x, y; i--;) {
        cin >> x >> y;
        a += 3 * x;
        b += 3 * x;
        b += 3 * min(6 - x, y);
    }
    cout << (a >= 66 && b >= 130 ? "Nice" : "Nae ga wae");
}