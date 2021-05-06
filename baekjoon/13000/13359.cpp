#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(9);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, p;
    cin >> n >> p;

    int k = 1;
    double ans = 1.0 * p * k / (n + 1);

    for (;;) {
        ++k;
        double nxt = ans * k / (k - 1) * 1.0 * (n - p + k) / (n + k);
        if (nxt < ans) break;
        ans = nxt;
    }
    cout << ans;
}