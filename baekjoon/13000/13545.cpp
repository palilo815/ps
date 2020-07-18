#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
struct query {
    int l, r, i;
    query(int l, int r, int i): l(l), r(r), i(i) {}
};

const int M = 1e5;
const int max_sq = 317;

vector<query> vt[max_sq];
int a[M + 1], ans[M];
int fst[M << 1 | 1], lst[M << 1 | 1];

void solve(vector<query>& vt, int s, int e) {
    memset(fst, -1, sizeof(fst));
    memset(lst, -1, sizeof(lst));
    sort(vt.begin(), vt.end(), [&](auto & a, auto & b) -> bool {
        return a.r < b.r;
    });

    int res2 = 0;
    for (auto& [l, r, i] : vt) {
        for (; s < r; ++s) {
            lst[a[s]] = s;
            if (s >= e)
                ~fst[a[s]] ? (res2 = max(res2, s - fst[a[s]])) : (fst[a[s]] = s);
        }

        int res1 = 0;
        for (int j = min(r, e); l < j; ++l)
            res1 = max(res1, lst[a[l]] - l);
        ans[i] = max(res1, res2);
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> a[i + 1];
    loop(i, N) a[i + 1] += a[i];
    loop(i, N + 1) a[i] += M;
    N = sqrt(N) + 1;

    int Q; cin >> Q;
    loop(i, Q) {
        int l, r; cin >> l >> r;
        --l;
        vt[l / N].emplace_back(l, ++r, i);
    }

    loop(i, N + 1) if (!vt[i].empty())
        solve(vt[i], i * N, (i + 1) * N);

    loop(i, Q) cout << ans[i] << '\n';
    return 0;
}