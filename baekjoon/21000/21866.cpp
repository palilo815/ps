#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int sum = 0;
    for (int i = 0, x; i < 9; ++i) {
        cin >> x;
        sum += x;
        if (x > (i / 2 + 1) * 100) {
            return cout << "hacker", 0;
        }
    }
    cout << (sum >= 100 ? "draw" : "none");
}