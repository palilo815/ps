#include <bits/stdc++.h>
using namespace std;

struct elem {
    int val, idx;
};
struct query {
    int l, r, k, idx;
};

const int mxN = 1e5;

elem a[mxN + 1];
query q[mxN];
int ans[mxN], bit[mxN + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> a[i].val;
        a[i].idx = i + 1;
    }

    int M;
    cin >> M;
    for (int i = 0; i < M; ++i) {
        cin >> q[i].l >> q[i].r >> q[i].k;
        --q[i].l;
        q[i].idx = i;
    }

    a[N].val = -1;
    sort(a, a + N, [&](auto& a, auto& b) {
        return a.val > b.val;
    });
    sort(q, q + M, [&](auto& a, auto& b) {
        return a.k > b.k;
    });

    auto update = [&](int i) {
        for (; i <= N; i += i & -i)
            ++bit[i];
    };
    auto read = [&](int i) {
        int ret = 0;
        for (; i; i -= i & -i)
            ret += bit[i];
        return ret;
    };

    for (int i = 0, j = 0; j < M; ++j) {
        while (a[i].val > q[j].k) update(a[i++].idx);
        ans[q[j].idx] = read(q[j].r) - read(q[j].l);
    }

    for (int i = 0; i < M; ++i)
        cout << ans[i] << '\n';
}