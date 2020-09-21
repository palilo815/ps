#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

const int mxX = 1e5;

int x[mxX + 1], y[mxX];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int X, Y, M;
    cin >> X >> Y >> M;
    loop(i, X) cin >> x[i];
    loop(i, Y) cin >> y[i];
    x[X] = INT_MAX;

    vector<int> ans;
    for (int i = 0, j = 0; i < X || j < Y;) {
        if (M > x[i]) {
            M -= x[i++];
            ans.emplace_back(-i);
        } else {
            if (j == Y) {
                ans = {0};
                break;
            }
            M += y[j++];
            ans.emplace_back(j);
        }
    }
    for (int& x : ans) cout << x << '\n';
    return 0;
}