#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll mod = 1e9 + 7;

void solve() {
    priority_queue<ll, vector<ll>, greater<ll>> pq;

    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        ll x; cin >> x;
        pq.emplace(x);
    }

    ll ans = 1;
    while (pq.size() > 1) {
        ll x = pq.top(); pq.pop();
        ll y = pq.top(); pq.pop();
        pq.emplace(x * y);

        ans = ans * (x * y % mod) % mod;
    }
    cout << ans << '\n';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) solve();
    return 0;
}