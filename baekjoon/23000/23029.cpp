#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    array<int, 3> dp {}, prv;
    for (int x; n--;) {
        dp.swap(prv);
        cin >> x;
        dp[0] = *max_element(prv.begin(), prv.end());
        dp[1] = prv[0] + x;
        dp[2] = prv[1] + x / 2;
    }
    cout << *max_element(dp.begin(), dp.end());
}