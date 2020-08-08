#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    priority_queue<ll, vector<ll>, greater<ll>> pq;
    int N, M; cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        ll x; cin >> x;
        pq.emplace(x);
    }

    while (M--) {
        ll x = pq.top(); pq.pop();
        ll y = pq.top(); pq.pop();
        pq.emplace(x + y), pq.emplace(x + y);
    }

    ll ans = 0;
    while (!pq.empty()) {
        ll x = pq.top(); pq.pop();
        ans += x;
    }
    cout << ans;
    return 0;
}