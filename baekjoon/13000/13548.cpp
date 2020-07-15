#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;
struct query {
    int l, r, i;
};

const int M = 1e5 + 1;

int A[M], cnt[M], total[M];

query q[M];
int ans[M], res;

void insert(int i) {
    int n = A[i];
    --total[cnt[n]];
    res = max(res, ++cnt[n]);
    ++total[cnt[n]];
}
void erase(int i) {
    int n = A[i];
    if (res == cnt[n] && total[cnt[n]] == 1) --res;
    --total[cnt[n]];
    ++total[--cnt[n]];
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    LOOP(i, N) cin >> A[i];
    int Q; cin >> Q;
    LOOP(i, Q) q[i].i = i;
    LOOP(i, Q) cin >> q[i].l >> q[i].r;

    int sqrt_N = sqrt(N);
    sort(q + 1, q + Q + 1, [&](auto & a, auto & b) -> bool {
        int A = a.l / sqrt_N, B = b.l / sqrt_N;
        return A == B ? a.r < b.r : A < B;
    });

    total[0] = N;
    int l = q[1].l, r = q[1].r;
    for (int i = l; i <= r; ++i)
        insert(i);
    ans[q[1].i] = res;

    for (int j = 2; j <= Q; ++j) {
        auto& [L, R, i] = q[j];
        while (l < L) erase(l++);
        while (l > L) insert(--l);
        while (R < r) erase(r--);
        while (R > r) insert(++r);
        ans[i] = res;
    }
    LOOP(i, Q) cout << ans[i] << '\n';
    return 0;
}