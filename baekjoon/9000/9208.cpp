#include <bits/stdc++.h>
using namespace std;

bool solve() {
    int m, n;
    cin >> m >> n;

    vector<pair<int, int>> a;
    a.reserve(n << 1);
    for (int i = 0, l, r; i < n; ++i) {
        cin >> l >> r, ++r;
        if (l < r)
            a.emplace_back(l, r), a.emplace_back(l + m, r + m);
        else
            a.emplace_back(l, r + m);
    }
    if (n > m) return false;

    n = a.size();
    sort(a.begin(), a.end(), [&](auto& a, auto& b) {
        return a.first < b.first;
    });

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0, target = 0;; ++target) {
        if (pq.empty()) {
            if (i == n) return true;
            target = max(target, a[i].first);
        }

        for (; i < n && a[i].first == target; ++i)
            pq.emplace(a[i].second);

        if (pq.top() <= target) return false;
        pq.pop();
    }
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) cout << (solve() ? "YES\n" : "NO\n");
}