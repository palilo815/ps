#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using ll = long long;
struct query {
    int l, r, i;
    query(int l, int r, int i) : l(l), r(r), i(i) {}
};

const int M = 1e5;
const int max_sq = 316;

int a[M], fenwick[M + 1];
vector<query> q[max_sq + 1];
ll res = 0, ans[M];

void update(int i, int v) {
    for (; i <= M; i += i & -i)
        fenwick[i] += v;
}
int read(int i) {
    int ret = 0;
    for (; i; i -= i & -i)
        ret += fenwick[i];
    return ret;
}
void apply(int n, int v, bool l) {
    if (l) res += v * read(n - 1);
    else res += v * (read(M) - read(n));
    update(n, v);
}
void solve(vector<query>& q) {
    if (q.empty()) return;
    sort(q.begin(), q.end(), [&](auto & a, auto & b) -> bool {
        return a.r == b.r ? a.l < b.l : a.r < b.r;
    });

    res = 0;
    memset(fenwick, 0, sizeof(fenwick));

    int l = q[0].l, r = q[0].r, sz = q.size();
    for (int i = r - 1; i ^ (l - 1); --i)
        apply(a[i], 1, 1);
    ans[q[0].i] = res;

    for (int j = 1; j ^ sz; ++j) {
        auto& [L, R, i] = q[j];
        while (L < l) apply(a[--l], 1, 1);
        while (r < R) apply(a[r++], 1, 0);
        while (l < L) apply(a[l++], -1, 1);
        while (R < r) apply(a[--r], -1, 0);
        ans[i] = res;
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, Q; cin >> N >> Q;
    loop(i, N) cin >> a[i];
    copy(a, a + N, fenwick);

    sort(fenwick, fenwick + N);
    int N2 = unique(fenwick, fenwick + N) - fenwick;
    loop(i, N) a[i] = lower_bound(fenwick, fenwick + N2, a[i]) - fenwick + 1;

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