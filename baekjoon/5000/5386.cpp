#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    for (int s, k; T--;) {
        cin >> s >> k;
        if (k & 1)
            cout << (s & 1) << '\n';
        else {
            s %= (k + 1);
            cout << (s == k ? k : s & 1) << '\n';
        }
    }
}