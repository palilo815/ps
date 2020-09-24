#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct elem {
    ll dp;
    int i;
    elem(ll dp, int i) : dp(dp), i(i) {}
    bool operator<(const elem& rhs) const {
        return dp < rhs.dp;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, D;
    cin >> N >> D;

    priority_queue<elem> pq;
    ll ans = LLONG_MIN;
    for (int i = 0, x; i < N; ++i) {
        while (!pq.empty() && pq.top().i < i - D) pq.pop();
        cin >> x;
        ll dp = pq.empty() ? x : (x + pq.top().dp);
        ans = max(ans, dp);
        if (dp > 0) pq.emplace(dp, i);
    }
    cout << ans;
    return 0;
}