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

    for (int d = 0; d < 7; ++d) {
        cout << (1 << d < n ? 'B' : 'A');
        for (int i = 1; i < n; ++i)
            cout << (i >> d & 1 ? 'A' : 'B');
        cout << '\n';
    }
}