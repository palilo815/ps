#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e3;

int a[mxN];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
        cin >> a[i];

    sort(a, a + n);

    int k = -1;
    unordered_set<int> st;
    for (int m = 0; m < n - 1; ++m) {
        for (int i = 0; i <= m; ++i)
            st.emplace(a[i] + a[m]);
        for (int i = max(m, k) + 1; i < n; ++i)
            if (st.count(a[i] - a[m]))
                k = i;
    }
    cout << a[k];
}