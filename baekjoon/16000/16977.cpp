#include <bits/stdc++.h>
#define left (i << 1)
#define right (i << 1 | 1)
using namespace std;

const int mxN = 1e5;

struct _segment {
    int h, l, r;
};
struct _query {
    int l, r, w, i;
};

_query q[mxN];
_segment a[mxN + 1];
int N, segT[mxN << 1];

void update(int i, int v) {
    segT[i += N] = v;
    while (i >>= 1) segT[i] = max(segT[left], segT[right]);
}
int mn_query(int l, int r) {
    int ret = INT_MAX;
    for (l += N, r += N; l != r; l >>= 1, r >>= 1) {
        if (l & 1) ret = min(ret, segT[l++]);
        if (r & 1) ret = min(ret, segT[--r]);
    }
    return ret;
}
int mx_query(int l, int r) {
    int ret = 0;
    for (l += N, r += N; l != r; l >>= 1, r >>= 1) {
        if (l & 1) ret = max(ret, segT[l++]);
        if (r & 1) ret = max(ret, segT[--r]);
    }
    return ret;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i].h;

    vector<int> vt;
    for (int i = 0; i < N; ++i) {
        while (!vt.empty() && a[vt.back()].h >= a[i].h)
            vt.pop_back();
        if (!vt.empty()) a[i].l = vt.back() + 1;
        vt.emplace_back(i);
    }
    vt.clear();
    for (int i = N - 1; ~i; --i) {
        while (!vt.empty() && a[vt.back()].h >= a[i].h)
            vt.pop_back();
        a[i].r = vt.empty() ? N : vt.back();
        vt.emplace_back(i);
    }

    for (int i = 0; i < N; ++i)
        segT[N + i] = a[i].h;
    for (int i = N - 1; i; --i)
        segT[i] = min(segT[left], segT[right]);

    int Q;
    cin >> Q;

    for (int i = 0; i < Q; ++i) {
        cin >> q[i].l >> q[i].r >> q[i].w;
        --q[i].l, q[i].i = i;
    }

    vt.resize(Q);
    for (int i = 0; i < Q; ++i)
        vt[i] = mn_query(q[i].l, q[i].l + q[i].w);

    sort(q, q + Q, [&](auto& a, auto& b) {
        return a.w > b.w;
    });
    sort(a, a + N, [&](auto& a, auto& b) {
        return a.r - a.l > b.r - b.l;
    });
    memset(segT, 0, sizeof(segT));

    for (int i = 0, j = 0; i < Q; ++i) {
        // a[N] is sentinel
        for (; a[j].r - a[j].l >= q[i].w; ++j)
            update(a[j].l, a[j].h);
        vt[q[i].i] = max(vt[q[i].i], mx_query(q[i].l, q[i].r - q[i].w + 1));
    }

    for (auto& x : vt)
        cout << x << '\n';
}