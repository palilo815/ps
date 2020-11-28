#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;

    vector<int> a(N);
    for (int& x : a) cin >> x;

    int total = accumulate(a.begin(), a.end(), 0, [&](auto& a, auto& b) {
        return a ^ b;
    });

    int ans = total;
    for (int& x : a)
        ans = max(ans, total ^ x);
    cout << ans << ans;
}