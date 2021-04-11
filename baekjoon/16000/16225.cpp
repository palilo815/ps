#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<pair<int, int>> vt(n);
    for (auto& [a, _] : vt) cin >> a;
    for (auto& [_, b] : vt) cin >> b;

    sort(vt.begin(), vt.end(), [&](auto& a, auto& b) {
        return a.second < b.second;
    });

    int64_t ans = vt[0].first;

    priority_queue<int> pq;
    for (int i = 1; i < n - 1; i += 2) {
        pq.emplace(vt[i].first);
        pq.emplace(vt[i + 1].first);

        ans += pq.top();
        pq.pop();
    }
    cout << ans;
}