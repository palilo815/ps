#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using pli = pair<ll, int>;

const int mxN = 5e5;

pll a[mxN + 1];
pli b[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;
    loop(i, N) cin >> a[i].first >> a[i].second;
    loop(i, M) cin >> b[i].first >> b[i].second;

    sort(a, a + N, [&](auto& a, auto& b) {
        return a.first < b.first;
    });
    sort(b, b + M, [&](auto& a, auto& b) {
        return a.first < b.first;
    });
    a[N].first = LLONG_MAX;

    priority_queue<ll, vector<ll>, greater<ll>> pq;
    int ans = 0;
    for (int i = 0, j = 0; i < M; ++i) {
        while (a[j].first <= b[i].first)
            pq.emplace(a[j++].second);
        while (!pq.empty() && pq.top() < b[i].first)
            pq.pop();

        int cnt = min(b[i].second, (int)pq.size());
        ans += cnt;
        while (cnt--) pq.pop();
    }
    cout << ans;
    return 0;
}