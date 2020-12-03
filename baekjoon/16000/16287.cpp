#include <bits/stdc++.h>
using namespace std;

const int mxN = 5e3;

int a[mxN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int w, n;
    cin >> w >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    vector<bool> v(w + 1);

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int val = w - a[i] - a[j];
            if (val >= 0 && v[val])
                return cout << "YES", 0;
        }
        for (int j = 0; j < i; ++j) {
            int val = a[i] + a[j];
            if (val <= w)
                v[val] = true;
        }
    }
    cout << "NO";
}