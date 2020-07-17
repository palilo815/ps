#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using ll = long long;
struct query {
    int l, r, i;
    query(int l, int r, int i) : l(l), r(r), i(i) {}
};

const int M = 1e5;

int K, a[M];
vector<query> q[317];
ll res, ans[M], fenwick[M + 1];

void update(int i, int v) {
    for (; i <= M; i += i & -i)
        fenwick[i] += v;
}
ll read(int i) {
    ll ret = 0;
    for (; i; i -= i & -i)
        ret += fenwick[i];
    return ret;
}
void apply(int n, int v) {
    if (v == -1) update(n, v);
    res += v * read(min(M, n + K));
    res -= v * read(max(0, n - K - 1));
    if (v == 1) update(n, v);
}
void solve(vector<query>& q) {
    if (q.empty()) return;
    sort(q.begin(), q.end(), [&](auto & a, auto & b) -> bool {
        return a.r == b.r ? a.l < b.l : a.r < b.r;
    });

    res = 0;
    memset(fenwick, 0, sizeof(fenwick));

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

    int N; cin >> N >> K;
    loop(i, N) cin >> a[i];

    int sqrt_N = sqrt(N);
    int Q; cin >> Q;
    loop(i, Q) {
        int l, r; cin >> l >> r;
        --l;
        q[l / sqrt_N].emplace_back(l, r, i);
    }

    loop(i, 317) solve(q[i]);
    loop(i, Q) cout << ans[i] << '\n';
    return 0;
}