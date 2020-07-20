#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define left (i<<1)
#define right (i<<1|1)
using namespace std;
using ll = long long;
struct q_add {
    int l, r, k;
};
struct q_kth {
    int l, r;
    ll k;
};

const int MAX = 1e5;
const int seg_N = 524288;

int num[MAX << 2];
q_add add[MAX];
q_kth kth[MAX];

ll segT[seg_N << 1];
int lazy[seg_N << 1], sz[seg_N << 1];
int lo[MAX], hi[MAX];

void prop(int i) {
    segT[i] += (ll)lazy[i] * sz[i];
    if (i < seg_N) lazy[left] += lazy[i], lazy[right] += lazy[i];
    lazy[i] = 0;
}
void update(int l, int r, int ql, int qr, int i) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {++lazy[i]; return;}
    if (lazy[i]) prop(i);

    int m = (l + r) >> 1;
    update(l, m, ql, qr, left), update(m, r, ql, qr, right);
    segT[i] = segT[left] + segT[right] + (ll)lazy[left] * sz[left] + (ll)lazy[right] * sz[right];
}
ll query(int l, int r, int ql, int qr, int i) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return segT[i] + (ll)lazy[i] * sz[i];
    if (lazy[i]) prop(i);

    int m = (l + r) >> 1;
    return query(l, m, ql, qr, left) + query(m, r, ql, qr, right);
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M, Q; cin >> N >> M >> Q;
    loop(i, M) cin >> add[i].l >> add[i].r >> add[i].k;
    loop(i, Q) cin >> kth[i].l >> kth[i].r >> kth[i].k;

    loop(i, M) {
        num[i << 1] = --add[i].l;
        num[i << 1 | 1] = add[i].r;
    }
    loop(i, Q) {
        num[(M + i) << 1] = --kth[i].l;
        num[(M + i) << 1 | 1] = kth[i].r;
    }

    sort(num, num + ((M + Q) << 1));
    N = unique(num, num + ((M + Q) << 1)) - num;

    loop(i, N - 1) sz[seg_N + i] = num[i + 1] - num[i];
    for (int i = seg_N - 1; i; --i)
        sz[i] = sz[left] + sz[right];

    loop(i, M) {
        add[i].l = lower_bound(num, num + N, add[i].l) - num;
        add[i].r = lower_bound(num, num + N, add[i].r) - num;
    }
    loop(i, Q) {
        kth[i].l = lower_bound(num, num + N, kth[i].l) - num;
        kth[i].r = lower_bound(num, num + N, kth[i].r) - num;
    }
    sort(add, add + M, [&](auto & a, auto & b) -> bool {
        return a.k < b.k;
    });
    fill_n(hi, Q, M);

    while (1) {
        vector<vector<int>> vt(M);
        bool done = true;
        loop(i, Q) if (lo[i] ^ hi[i]) {
            vt[(lo[i] + hi[i]) >> 1].emplace_back(i);
            done = false;
        }
        if (done) break;

        memset(segT, 0, sizeof(segT));
        memset(lazy, 0, sizeof(lazy));

        loop(m, M) {
            update(0, seg_N, add[m].l, add[m].r, 1);
            for (int& i : vt[m])
                query(0, seg_N, kth[i].l, kth[i].r, 1) < kth[i].k ? (lo[i] = m + 1) : (hi[i] = m);
        }
    }
    loop(i, Q) cout << add[lo[i]].k << '\n';
    return 0;
}