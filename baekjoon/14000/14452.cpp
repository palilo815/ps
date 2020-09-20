#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

const int mxN = 1e4;

int N, T, a[mxN];

bool valid(int m) {
    priority_queue<int, vector<int>, greater<int>> pq;
    loop(i, m) pq.emplace(a[i]);

    for (int i = m; i < N; ++i) {
        int t = pq.top();
        pq.pop();
        if (t + a[i] > T) return false;
        pq.emplace(t + a[i]);
    }
    return true;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> N >> T;
    loop(i, N) cin >> a[i];

    int lo = 1, hi = N;
    while (lo ^ hi) {
        int m = (lo + hi) >> 1;
        valid(m) ? (hi = m) : (lo = m + 1);
    }
    cout << lo;
    return 0;
}