#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    priority_queue<int64_t, vector<int64_t>, greater<int64_t>> pq;
    for (int x; n--;) {
        cin >> x;
        pq.emplace(x);
    }

    int64_t ans = 0;
    while (pq.size() != 1) {
        const auto x = pq.top();
        pq.pop();
        const auto y = pq.top();
        pq.pop();

        ans += x + y;
        pq.emplace(x + y);
    }
    cout << ans << '\n';
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
}