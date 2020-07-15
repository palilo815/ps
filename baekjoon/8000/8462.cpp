#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;
using ll = long long;
struct query {
    int l, r, i;
};

const int max_N = 1e5 + 1;
const int max_a = 1e6 + 1;

int a[max_N], cnt[max_a];

query q[max_N];
ll ans[max_N];

ll apply(int i, int v) {
    ll n = a[i];
    ll ret = -n * cnt[n] * cnt[n];
    cnt[n] += v;
    return ret + n * cnt[n] * cnt[n];
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, Q; cin >> N >> Q;
    LOOP(i, N) cin >> a[i];
    LOOP(i, Q) q[i].i = i;
    LOOP(i, Q) cin >> q[i].l >> q[i].r;

    int sqrt_N = sqrt(N);
    sort(q + 1, q + Q + 1, [&](auto & a, auto & b) -> bool {
        int A = a.l / sqrt_N, B = b.l / sqrt_N;
        return A == B ? a.r < b.r : A < B;
    });

    ll res = 0;
    int l = q[1].l, r = q[1].r;
    for (int i = l; i <= r; ++i)
        res += apply(i, 1);
    ans[q[1].i] = res;

    for (int j = 2; j <= Q; ++j) {
        auto& [L, R, i] = q[j];
        while (l < L) res += apply(l++, -1);
        while (l > L) res += apply(--l, 1);
        while (R < r) res += apply(r--, -1);
        while (R > r) res += apply(++r, 1);
        ans[i] = res;
    }
    LOOP(i, Q) cout << ans[i] << '\n';
    return 0;
}