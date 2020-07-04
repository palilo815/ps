#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define x first
#define y second
using namespace std;
using ll = long long;
using p = pair<int, int>;

p poly[50];

ll area(int i) {
    p& b = poly[i], & c = poly[i + 1];
    return (ll)(b.x - poly[0].x) * (c.y - poly[0].y) -
           (ll)(b.y - poly[0].y) * (c.x - poly[0].x);
}
ll solve() {
    int N; cin >> N;
    loop(i, N) cin >> poly[i].x >> poly[i].y;

    ll ret = 0;
    for (int i = 1; i < N - 1; ++i)
        ret += area(i);
    return ret > 0 ? ret : -ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    ll ans = 0;
    while (T--) ans += solve();
    cout << (ans >> 1);
    return 0;
}