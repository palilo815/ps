#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
struct query {
    int l, r, i;
    query(int l, int r, int i) : l(l), r(r), i(i) {}
};

const int max_N = 1e5;
const int max_p = 2e5 + 1;

int p[max_N], cnt[max_p], total[max_N];

vector<query> q[317];
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
void solve(vector<query>& q) {
    if (q.empty()) return;
    sort(q.begin(), q.end(), [&](auto & a, auto & b) -> bool {
        return a.r == b.r ? a.l < b.l : a.r < b.r;
    });

    res = 0;
    memset(cnt, 0, sizeof(cnt));
    memset(total, 0, sizeof(total));

    int l = q[0].l, r = q[0].r, sz = q.size();
    for (int i = l; i < r; ++i)
        insert(i);
    ans[q[0].i] = res;

    for (int j = 1; j ^ sz; ++j) {
        auto& [L, R, i] = q[j];
        while (l > L) insert(--l);
        while (R > r) insert(r++);
        while (l < L) erase(l++);
        while (R < r) erase(--r);
        ans[i] = res;
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, Q; cin >> N >> Q;
    loop(i, N) cin >> p[i];
    loop(i, N) p[i] += 100000;

    int sqrt_N = sqrt(N);
    loop(i, Q) {
        int l, r; cin >> l >> r;
        --l;
        q[l / sqrt_N].emplace_back(l, r, i);
    }

    loop(i, sqrt_N + 1) solve(q[i]);
    loop(i, Q) cout << ans[i] << '\n';
    return 0;
}