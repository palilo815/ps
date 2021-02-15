#include <bits/stdc++.h>
using namespace std;

struct segtree {
    struct node {
        int mn, mx;
        void merge(const node rhs) {
            if (rhs.mn < mn) mn = rhs.mn;
            if (rhs.mx > mx) mx = rhs.mx;
        }
    };

    vector<node> tr;
    int n;

    segtree(const vector<int>& a) : n(a.size()) {
        tr.resize(n << 1);
        for (int i = 0; i < n; ++i)
            tr[n + a[i]] = {i, i + 1};
        for (int i = n - 1; i; --i)
            pull(i);
    }
    inline void pull(int i) {
        tr[i].mn = min(tr[i << 1].mn, tr[i << 1 | 1].mn);
        tr[i].mx = max(tr[i << 1].mx, tr[i << 1 | 1].mx);
    }
    void update(int u, int v) {
        swap(tr[u += n], tr[v += n]);
        for (u >>= 1; u; u >>= 1) pull(u);
        for (v >>= 1; v; v >>= 1) pull(v);
    }
    node query(int l, int r) const {
        node ret = {INT_MAX, INT_MIN};
        for (l += n, r += n; l != r; l >>= 1, r >>= 1) {
            if (l & 1) ret.merge(tr[l++]);
            if (r & 1) ret.merge(tr[--r]);
        }
        return ret;
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

    vector<int> h(n);
    for (auto& x : h) cin >> x, --x;

    segtree segT(h);
    char op;
    for (int l, r; m--;) {
        cin >> op >> l >> r;
        if (op == '1') {
            --l, --r;
            swap(h[l], h[r]);
            segT.update(h[l], h[r]);
        } else {
            --l;
            auto res = segT.query(l, r);
            cout << (res.mx - res.mn == r - l ? "YES\n" : "NO\n");
        }
    }
}