#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
struct query {
    int l, r, i;
    query(int l, int r, int i) : l(l), r(r), i(i) {}
};

const int M = 5e5;
const int max_sq = 707;

int res, a[M], ans[M], cnt[M];
vector<query> q[max_sq + 1];

void apply(int n, int v) {
    if (cnt[n] == 2) --res;
    if ((cnt[n] += v) == 2) ++res;
}
void solve(vector<query>& q) {
    if (q.empty()) return;
    sort(q.begin(), q.end(), [&](auto & a, auto & b) -> bool {
        return a.r == b.r ? a.l < b.l : a.r < b.r;
    });

    res = 0;
    memset(cnt, 0, sizeof(cnt));

    int l = q[0].l, r = q[0].r, sz = q.size();
    for (int i = l; i ^ r; ++i)
        apply(a[i], 1);
    ans[q[0].i] = res;

    for (int j = 1; j ^ sz; ++j) {
        auto& [L, R, i] = q[j];
        while (L < l) apply(a[--l], 1);
        while (r < R) apply(a[r++], 1);
        while (l < L) apply(a[l++], -1);
        while (R < r) apply(a[--r], -1);
        ans[i] = res;
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, Q; cin >> N >> Q;
    loop(i, N) cin >> a[i];
    copy(a, a + N, cnt);

    sort(cnt, cnt + N);
    int N2 = unique(cnt, cnt + N) - cnt;
    loop(i, N) a[i] = lower_bound(cnt, cnt + N2, a[i]) - cnt;

    int sqrt_N = sqrt(N);
    loop(i, Q) {
        int l, r; cin >> l >> r;
        --l;
        q[l / sqrt_N].emplace_back(l, r, i);
    }
    loop(i, max_sq + 1) solve(q[i]);
    loop(i, Q) cout << ans[i] << '\n';
    return 0;
}