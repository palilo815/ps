#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n;
    string me, you;
    cin >> n >> me >> you;

    int same = 0, diff = 0;
    for (int i = 0; i < int(me.size()); ++i)
        me[i] == you[i] ? ++same : ++diff;

    if (n > same) {
        cout << same + (same + diff - n);
    } else {
        cout << n + diff;
    }
}