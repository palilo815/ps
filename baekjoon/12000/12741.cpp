#include <bits/stdc++.h>
using namespace std;

struct segtree {
    vector<int> a;
    vector<bool> tree;
    int sgN;

    segtree(int n) : sgN(1 << 32 - __builtin_clz(n - 1)), a(n) {
        for (auto& x : a) cin >> x;

        tree.resize(sgN << 1);
        fill(tree.begin() + sgN, tree.begin() + sgN + n, true);
        for (int i = sgN - 1; i; --i) pull(i);
    }
    inline int fst(int i) {
        int d = 31 - __builtin_clz(i);
        return (sgN >> d) * (i ^ 1 << d);
    }
    inline int lst(int i) {
        int d = 31 - __builtin_clz(i);
        return (sgN >> d) * ((i ^ 1 << d) + 1) - 1;
    }
    inline void pull(int i) {
        int idx = fst(i << 1 | 1);
        tree[i] = tree[i << 1] && tree[i << 1 | 1] && a[idx - 1] <= a[idx];
    }
    bool query(int l, int r) {
        int lval = INT_MIN, rval = INT_MAX;
        for (l += sgN, r += sgN; l != r; l >>= 1, r >>= 1) {
            if (l & 1) {
                if (!tree[l] || lval > a[fst(l)]) return false;
                lval = a[lst(l)];
                ++l;
            }
            if (r & 1) {
                --r;
                if (!tree[r] || a[lst(r)] > rval) return false;
                rval = a[fst(r)];
            }
        }
        return lval <= rval;
    }
    void update(int u, int v) {
        swap(a[u], a[v]);
        for (u = (u + sgN) >> 1; u; u >>= 1) pull(u);
        for (v = (v + sgN) >> 1; v; v >>= 1) pull(v);
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    segtree segT(n);

    char op;
    for (int l, r; m--;) {
        cin >> op >> l >> r;
        if (op == '1')
            cout << (segT.query(l - 1, r) ? "CS204\n" : "HSS090\n");
        else
            segT.update(l - 1, r - 1);
    }
}