#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using ll = long long;
struct query {
    int l, r, i;
    query(int l, int r, int i) : l(l), r(r), i(i) {}
};

const int M = 1e5;
const int max_sq = 317;

int a[M], num[M], c1[M], c2[M];
vector<query> q[max_sq];
ll ans[M];

void solve(vector<query>& q, int s, int e) {
    int s0 = s;
    memset(c1, 0, sizeof(c1));
    memset(c2, 0, sizeof(c2));
    sort(q.begin(), q.end(), [&](auto & a, auto & b) -> bool {
        return a.r < b.r;
    });

    ll res2 = 0;
    for (auto& [l, r, id] : q) {
        for (; s < r; ++s) {
            ++c1[a[s]];
            if (s >= e) res2 = max(res2, (ll)num[a[s]] * ++c2[a[s]]);
        }

        ll res1 = 0;
        for (int i = s0; i < l; ++i)
            --c1[a[i]];
        for (int i = l, j = min(r, e); i < j; ++i)
            res1 = max(res1, (ll)num[a[i]] * c1[a[i]]);
        for (int i = s0; i < l; ++i)
            ++c1[a[i]];
        ans[id] = max(res1, res2);
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, Q; cin >> N >> Q;
    loop(i, N) cin >> a[i];

    copy(a, a + N, num);
    sort(num, num + N);
    int sz = unique(num, num + N) - num;
    loop(i, N) a[i] = lower_bound(num, num + sz, a[i]) - num;

    N = sqrt(N - 1) + 1;
    loop(i, Q) {
        int l, r; cin >> l >> r;
        --l;
        q[l / N].emplace_back(l, r, i);
    }

    loop(i, N + 1) if (!q[i].empty())
        solve(q[i], i * N, (i + 1) * N);

    loop(i, Q) cout << ans[i] << '\n';
    return 0;
}