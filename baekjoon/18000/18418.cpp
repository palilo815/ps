#include <bits/stdc++.h>
using namespace std;
struct berry {
    int x, t;
};

const int mx = 1e5;

berry a[mx + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> a[i].x >> a[i].t;
    sort(a, a + N + 1, [&](auto & a, auto & b) {
        return a.x < b.x;
    });

    int ans = max(a[N].x, a[N].t);
    for (int i = N; i; --i)
        ans = max(a[i - 1].t, ans + a[i].x - a[i - 1].x);
    cout << ans;
    return 0;
}