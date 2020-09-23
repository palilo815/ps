#include <bits/stdc++.h>
using namespace std;
struct ord_x {
    int x, y;
    bool operator<(const ord_x& rhs) const {
        return x == rhs.x ? y < rhs.y : x < rhs.x;
    }
};
struct ord_y {
    int x, y;
    bool operator<(const ord_y& rhs) const {
        return y == rhs.y ? x < rhs.x : y < rhs.y;
    }
};

const int mxN = 3e5;

ord_x x[mxN];
ord_y y[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> x[i].x >> x[i].y;

    memmove(y, x, sizeof(ord_x) * N);
    sort(x, x + N);
    sort(y, y + N);

    int Q;
    cin >> Q;
    for (int x1, x2, y1, y2, ans; Q--;) {
        cin >> x1 >> y1 >> x2 >> y2;
        ans = upper_bound(y, y + N, ord_y {x2, y1}) - lower_bound(y, y + N, ord_y {x1, y1}) +
              upper_bound(y, y + N, ord_y {x2, y2}) - lower_bound(y, y + N, ord_y {x1, y2}) +
              upper_bound(x, x + N, ord_x {x1, y2 - 1}) - lower_bound(x, x + N, ord_x {x1, y1 + 1}) +
              upper_bound(x, x + N, ord_x {x2, y2 - 1}) - lower_bound(x, x + N, ord_x {x2, y1 + 1});
        cout << ans << '\n';
    }
    return 0;
}