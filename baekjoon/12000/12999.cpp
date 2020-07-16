#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;
struct query {
    int l, r, i;
};

const int max_N = 1e5 + 1;
const int max_p = 2e5 + 1;

int p[max_N], cnt[max_p], total[max_N];

query q[max_N];
int ans[max_N], res;

void insert(int i) {
    int n = p[i];
    --total[cnt[n]];
    res = max(res, ++cnt[n]);
    ++total[cnt[n]];
}
void erase(int i) {
    int n = p[i];
    if (res == cnt[n] && total[cnt[n]] == 1) --res;
    --total[cnt[n]];
    ++total[--cnt[n]];
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, Q; cin >> N >> Q;
    LOOP(i, N) cin >> p[i];
    LOOP(i, N) p[i] += 100000;
    LOOP(i, Q) q[i].i = i;
    LOOP(i, Q) cin >> q[i].l >> q[i].r;

    int sqrt_N = sqrt(N);
    sort(q + 1, q + Q + 1, [&](auto & a, auto & b) -> bool {
        int A = a.l / sqrt_N, B = b.l / sqrt_N;
        return A == B ? a.r < b.r : A < B;
    });

    int l = q[1].l, r = q[1].r;
    for (int i = l; i <= r; ++i)
        insert(i);
    ans[q[1].i] = res;

    for (int j = 2; j <= Q; ++j) {
        auto& [L, R, i] = q[j];
        while (l > L) insert(--l);
        while (R > r) insert(++r);
        while (l < L) erase(l++);
        while (R < r) erase(r--);
        ans[i] = res;
    }
    LOOP(i, Q) cout << ans[i] << '\n';
    return 0;
}