#include <bits/stdc++.h>
using namespace std;
struct event {
    int s, e;
};

event a[20];

void solve(int N) {
    sort(a, a + N, [&](auto & a, auto & b) {
        return a.e < b.e;
    });
    int t = 0, ans = 0;
    for (int i = 0; i < N; ++i)
        if (t <= a[i].s)
            ++ans, t = a[i].e;
    cout << ans << '\n';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--)
        for (int i = 0;; ++i) {
            cin >> a[i].s >> a[i].e;
            if (!a[i].e) {solve(i); break;}
        }
    return 0;
}