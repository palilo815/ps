#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("out", "w", stdout);
    freopen("in", "r", stdin);
#endif
    int n, k;
    int64_t m;
    cin >> n >> k >> m;

    vector<pair<int, int>> a(n);
    for (auto& [p, c] : a) cin >> p >> c;

    sort(a.begin(), a.end(), [&](auto& a, auto& b) {
        return a.second == b.second ? a.first < b.first : a.second < b.second;
    });

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < k; ++i) {
        m -= a[i].second;
        if (m < 0) return cout << i, 0;
        pq.emplace(a[i].first - a[i].second);
    }

    sort(a.begin() + k, a.end());
    for (int i = k; i < n; ++i) {
        if (a[i].first - a[i].second > pq.top()) {
            m -= pq.top() + a[i].second;
            pq.pop();
            pq.emplace(a[i].first - a[i].second);
        } else
            m -= a[i].first;
        if (m < 0) return cout << i, 0;
    }
    cout << n;
}