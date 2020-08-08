#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
struct event {
    int s, d;
};

const int mx = 1e4;

event a[mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> a[i].s >> a[i].d;
    sort(a, a + N, [&](auto & a, auto & b) {
        return a.s + a.d < b.s + b.d;
    });

    int ans = 0;
    for (int t = 0, i = 0; i < N; ++i)
        if (t <= a[i].s)
            ++ans, t = a[i].s + a[i].d;
    cout << ans;
    return 0;
}