#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int R, C;
    cin >> R >> C;
    vector<int> r(R), c(C);
    for (int& x : r) cin >> x;
    for (int& x : c) cin >> x;

    cout << (*max_element(r.begin(), r.end()) == *max_element(c.begin(), c.end()) ? "possible" : "impossible");
    return 0;
}