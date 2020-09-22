#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;
using p = pair<int, int>;

const int mxN = 1e5;

int a[mxN];
p b[mxN + 1];

void solve() {
    int N, M;
    cin >> N >> M;
    loop(i, N) cin >> a[i];
    loop(i, M) cin >> b[i].first >> b[i].second;

    sort(a, a + N);
    sort(b, b + M, [&](auto& a, auto& b) {
        return a.first < b.first;
    });
    b[M].first = INT_MAX;

    priority_queue<int, vector<int>, greater<int>> pq;
    int ans = 0;
    for (int i = 0, j = 0; i < N; ++i) {
        while (b[j].first <= a[i])
            pq.emplace(b[j++].second);
        while (!pq.empty() && pq.top() < a[i])
            pq.pop();

        if (!pq.empty())
            ++ans, pq.pop();
    }
    cout << ans << '\n';
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}