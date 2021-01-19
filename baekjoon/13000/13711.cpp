#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

int idx[mxN + 1];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        idx[x] = i;
    }

    vector<int> dp = {INT_MIN}; // sentinel
    for (int x; n--;) {
        cin >> x;
        x = idx[x];

        if (x > dp.back())
            dp.emplace_back(x);
        else
            *lower_bound(dp.begin(), dp.end(), x) = x;
    }
    cout << dp.size() - 1;
}