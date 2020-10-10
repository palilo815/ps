#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

pair<int, int> a[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i].second >> a[i].first;

    sort(a, a + N);

    int ans = 0;
    for (int i = 0, t = 0; i < N; ++i)
        if (t <= a[i].second)
            t = a[i].first, ++ans;
    cout << ans;
    return 0;
}