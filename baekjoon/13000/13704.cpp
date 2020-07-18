#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i^n;++i)
using namespace std;
using ll = long long;
struct query {
    int l, r, i;
    ll ord;
    query(int l = 0, int r = 0, int i = 0): l(l), r(r), i(i) {}
};

const int M = 1e5;
const int max_p = 17;
const int cnt_N = 1 << 20;

int K, a[M + 1], cnt[cnt_N];
ll res, ans[M];

query q[M];

ll hilbert(int r, int c, int pow, int rot) {
    if (!pow--) return 0;
    int half = 1 << pow;
    int seg = r < half ? (c < half ? 0 : 3) : (c < half ? 1 : 2);
    seg = (seg + rot) & 3;

    const int d_rot[4] = {3, 0, 0, 1};
    int R = r & (r ^ half), C = c & (c ^ half), ROT = (rot + d_rot[seg]) & 3;
    ll square = ll(1) << (pow << 1);
    ll ans = seg * square, add = hilbert(R, C, pow, ROT);
    ans += (seg == 1 || seg == 2) ? add : (square - add - 1);
    return ans;
}
void insert(int n) {
    res += cnt[n ^ K];
    ++cnt[n];
}
void erase(int n) {
    --cnt[n];
    res -= cnt[n ^ K];
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N >> K;
    for (int i = 1; i <= N; ++i) {
        cin >> a[i];
        a[i] ^= a[i - 1];
    }

    int Q; cin >> Q;
    loop(i, Q) cin >> q[i].l >> q[i].r;
    loop(i, Q) q[i].i = i;
    loop(i, Q) q[i].ord = hilbert(--q[i].l, q[i].r, max_p, 0);
    sort(q, q + Q, [&](auto & a, auto & b) -> bool {
        return a.ord < b.ord;
    });

    int l = 0, r = 1;
    res = (a[1] == K);
    ++cnt[0]; ++cnt[a[1]];

    loop(j, Q) {
        auto& [L, R, i, _] = q[j];
        while (L < l) insert(a[--l]);
        while (r < R) insert(a[++r]);
        while (l < L) erase(a[l++]);
        while (R < r) erase(a[r--]);
        ans[i] = res;
    }
    loop(i, Q) cout << ans[i] << '\n';
    return 0;
}