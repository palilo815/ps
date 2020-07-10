#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define x first
#define y second
using namespace std;
using p = pair<int, int>;

const int max_N = 1e5;

int M, idx[max_N];
p a[max_N], dp[max_N], segT[max_N << 1];

void update(int i, p v) {
    if (segT[i].x > v.x) return;
    for (segT[i] = v; i > 1; i >>= 1)
        segT[i >> 1] = max(segT[i], segT[i ^ 1]);
}
p query(int i) {
    p ret = {0, -1};
    for (int l = M + i, r = M << 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            if (segT[l].x > ret.x) ret = segT[l];
            ++l;
        }
        if (r & 1) {
            --r;
            if (segT[r].x > ret.x) ret = segT[r];
        }
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) {
        cin >> a[i].x >> a[i].y;
        idx[i] = a[i].x;
    }

    sort(idx, idx + N);
    M = unique(idx, idx + N) - idx;
    sort(a, a + N, [&](p & a, p & b) -> bool {
        return a.y == b.y ? a.x > b.x : a.y < b.y;
    });

    loop(i, N) {
        int id = lower_bound(idx, idx + M, a[i].x) - idx;
        dp[i] = query(id);
        ++dp[i].x;
        update(id + M, {dp[i].x, i});
    }

    auto ans = max_element(dp, dp + N);
    int i = ans - dp;
    cout << ans->x;
    while (~i) {
        cout << '\n' << a[i].x << ' ' << a[i].y;
        i = dp[i].y;
    }
    return 0;
}