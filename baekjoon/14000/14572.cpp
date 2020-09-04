#include <bits/stdc++.h>
#define left (i<<1)
#define right (i<<1|1)
using namespace std;
struct elem {
    int d, mask;
};

const int mxN = 1e5;

elem a[mxN + 1];
int N, oT[mxN << 1], aT[mxN << 1];

int query(int l, int r) {
    int cnt = r - l, OR = 0, AND = -1;
    for (l += N, r += N; l ^ r; l >>= 1, r >>= 1) {
        if (l & 1) {
            OR |= oT[l], AND &= aT[l];
            ++l;
        }
        if (r & 1) {
            --r;
            OR |= oT[r], AND &= aT[r];
        }
    }
    return __builtin_popcount(AND ^ OR) * cnt;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int K, D; cin >> N >> K >> D;
    for (int i = 0, m, x; i < N; ++i)
        for (cin >> m >> a[i].d; m; --m) {
            cin >> x;
            a[i].mask |= 1 << x;
        }

    sort(a, a + N, [&](auto & a, auto & b) {
        return a.d < b.d;
    });
    a[N].d = INT_MAX;

    for (int i = 0; i < N; ++i)
        oT[i + N] = a[i].mask;
    copy(oT + N, oT + N + N, aT + N);

    for (int i = N - 1; i; --i) {
        oT[i] = oT[left] | oT[right];
        aT[i] = aT[left] & aT[right];
    }

    int ans = 0;
    for (int i = 0, j = 0; j ^ N; ++i) {
        while (a[j].d - a[i].d <= D) ++j;
        ans = max(ans, query(i, j));
    }
    cout << ans;
    return 0;
}