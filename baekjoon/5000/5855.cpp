#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
using ll = long long;
using p = pair<int, int>;

const int max_N = 5e4;

p a[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, K; cin >> N >> K;
    for (int i = 0; i < N; ++i)
        cin >> a[i].x >> a[i].y;
    sort(a, a + N);

    set<p> st;
    ll ans = 0;
    for (int i = 0, j = 0; i < N; ++i) {
        for (; a[j].x + K <= a[i].x; ++j)
            st.erase({a[j].y, a[j].x});
        auto lo = st.lower_bound({a[i].y - K, INT_MAX});
        auto hi = st.upper_bound({a[i].y + K, INT_MIN});
        if (lo != hi) {
            if (ans || lo != --hi) {ans = -1; break;}
            ans = (ll)(K - a[i].x + lo->y) * (K - abs(a[i].y - lo->x));
        }
        st.emplace(a[i].y, a[i].x);
    }
    cout << ans;
    return 0;
}