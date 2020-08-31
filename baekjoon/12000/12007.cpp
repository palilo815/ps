#include <bits/stdc++.h>
using namespace std;
struct point {
    int x, y;
};

const int mxN = 5e4;

point a[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int mn, mx, ans1, ans2;

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i].x >> a[i].y;

    sort(a, a + N, [&](auto & a, auto & b) {
        return a.x < b.x;
    });
    mn = INT_MAX, mx = INT_MIN;
    for (int i = 1; i < N - 1; ++i)
        mn = min(mn, a[i].y), mx = max(mx, a[i].y);
    ans1 = min((a[N - 2].x - a[0].x) * ((max(mx, a[0].y) - min(mn, a[0].y))),
               (a[N - 1].x - a[1].x) * ((max(mx, a[N - 1].y) - min(mn, a[N - 1].y))));

    sort(a, a + N, [&](auto & a, auto & b) {
        return a.y < b.y;
    });
    mn = INT_MAX, mx = INT_MIN;
    for (int i = 1; i < N - 1; ++i)
        mn = min(mn, a[i].x), mx = max(mx, a[i].x);
    ans2 = min((a[N - 2].y - a[0].y) * ((max(mx, a[0].x) - min(mn, a[0].x))),
               (a[N - 1].y - a[1].y) * ((max(mx, a[N - 1].x) - min(mn, a[N - 1].x))));

    cout << min(ans1, ans2);
    return 0;
}