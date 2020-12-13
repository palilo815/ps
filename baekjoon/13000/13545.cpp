#include <bits/stdc++.h>
using namespace std;

struct query {
    int l, r, i;
    query(int l, int r, int i) : l(l), r(r), i(i) {}
};

const int mxN = 1e5;
const int max_sq = 317;

vector<query> vt[max_sq];
int a[mxN + 1], ans[mxN];
int fst[mxN << 1 | 1], lst[mxN << 1 | 1];

void solve(vector<query>& vt, int s, int e) {
    memset(fst, -1, sizeof(fst));
    memset(lst, -1, sizeof(lst));
    sort(vt.begin(), vt.end(), [&](auto& a, auto& b) {
        return a.r < b.r;
    });

    int res2 = 0;
    for (auto& [l, r, i] : vt) {
        for (; s < r; ++s) {
            lst[a[s]] = s;
            if (s >= e)
                ~fst[a[s]] ? res2 = max(res2, s - fst[a[s]]) : fst[a[s]] = s;
        }

        int res1 = 0;
        for (int j = min(r, e); l < j; ++l)
            res1 = max(res1, lst[a[l]] - l);
        ans[i] = max(res1, res2);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    partial_sum(a + 1, a + n + 1, a + 1);
    for (int i = 0; i <= n; ++i)
        a[i] += mxN;

    n = sqrt(n) + 1;

    int q;
    cin >> q;

    for (int l, r, i = 0; i < q; ++i) {
        cin >> l >> r;
        --l, ++r;
        vt[l / n].emplace_back(l, r, i);
    }

    for (int i = 0; i < n; ++i)
        if (!vt[i].empty())
            solve(vt[i], i * n, (i + 1) * n);

    for (int i = 0; i < q; ++i)
        cout << ans[i] << '\n';
}