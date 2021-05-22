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

    vector whose(n << 1, 'b');
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        whose[x - 1] = 'e';
    }

    int stk = 0, ans = 0;
    for (int i = n << 1; i--;) {
        if (whose[i] == 'b') ++stk;
        else if (stk)
            --stk, ++ans;
    }
    cout << ans;
}