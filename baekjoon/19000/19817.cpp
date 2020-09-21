#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using p = pair<int, int>;

const int mxN = 2e5;

p a[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> a[i].first;
        for (int j = 0, x; j < a[i].first; ++j) {
            cin >> x;
            if (a[i].second < x) a[i].second = x;
        }
    }

    auto mx = max_element(a, a + N, [&](auto& a, auto& b) { return a.second < b.second; })->second;
    ll ans = 0;
    for (int i = 0; i < N; ++i)
        ans += (ll)(mx - a[i].second) * a[i].first;
    cout << ans;
    return 0;
}