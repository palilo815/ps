#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int t;
    cin >> t;
    while (t--) {
        int64_t n;
        cin >> n;
        if (n % 9 == 0) {
            cout << "TAK\n";
        } else if (n % 3 == 0) {
            cout << "NIE\n";
        } else {
            cout << ((n % 3 == 2) ? "TAK\n" : "NIE\n");
        }
    }
}
