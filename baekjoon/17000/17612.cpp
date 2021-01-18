#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

struct info {
    int id;
    int64_t when;
};

info a[mxN];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (int i = 0; i < k; ++i)
        pq.emplace(0, i);

    for (int i = 0, w, where; i < n; ++i) {
        cin >> a[i].id >> w;
        w += pq.top().first;
        where = pq.top().second;
        a[i].when = int64_t(w) * mxN - where;
        pq.pop();
        pq.emplace(w, where);
    }

    sort(a, a + n, [&](auto& a, auto& b) {
        return a.when < b.when;
    });

    int64_t ans = 0;
    for (int i = 0; i < n; ++i)
        ans += int64_t(i + 1) * a[i].id;
    cout << ans;
}