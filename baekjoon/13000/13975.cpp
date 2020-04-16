#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    while (T--) {
        int N; cin >> N;
        for (int i = 0; i < N; ++i) {
            int x; cin >> x;
            pq.emplace(x);
        }

        ll ans = 0;
        while (pq.size() > 1) {
            ll a = pq.top(); pq.pop();
            ll b = pq.top(); pq.pop();
            ans += a + b;
            pq.emplace(a + b);
        }
        cout << ans << '\n';
        pq.pop();
    }
    return 0;
}