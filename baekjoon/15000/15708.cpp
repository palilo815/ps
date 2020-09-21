#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

int a[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, T, P;
    cin >> N >> T >> P;
    for (int i = 0; i < N; ++i)
        cin >> a[i];

    priority_queue<int> pq;
    int ans = 0;
    for (int i = 0, s = 0; i < N; ++i) {
        s += a[i];
        pq.emplace(a[i]);

        while (!pq.empty() && s > T - (long long)P * i) {
            s -= pq.top();
            pq.pop();
        }
        ans = max(ans, (int)pq.size());
    }
    cout << ans;
    return 0;
}