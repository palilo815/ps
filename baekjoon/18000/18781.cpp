#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<pair<int, int>> a(n);
    for (auto& [l, r] : a) cin >> l >> r;

    sort(a.begin(), a.end(), [&](auto& a, auto& b) {
        return a.first < b.first;
    });

    vector<int> f(n);
    f[0] = 1;
    for (int i = 1; i < n; ++i)
        f[i] = (f[i - 1] << 1) % mod;

    priority_queue<int, vector<int>, greater<int>> pq;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        while (!pq.empty() && pq.top() < a[i].first) pq.pop();
        ans += f[n - 1 - pq.size()];
        ans %= mod;
        pq.emplace(a[i].second);
    }
    cout << ans;
}