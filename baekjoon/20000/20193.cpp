#include <bits/stdc++.h>
using namespace std;

constexpr int mxX = 25e4;

struct point {
    int x, y, c;
};

template <typename node_t, typename tag_t>
struct lazy_seg {
    lazy_seg(int _n) : n(_n), height(__lg(_n - 1) + 1), size(1 << height),
                       tree(size << 1), lazy(size) {}

#define lson (i << 1)
#define rson (i << 1 | 1)
    void clear() {
        fill(tree.begin(), tree.end(), 0);
        fill(lazy.begin(), lazy.end(), 0);
    }
    void apply(int l, int r, node_t val) {
        apply(l, r, val, 0, mxX, 1);
    }
    node_t all_prod() { return tree[1]; }

private:
    const int n, height, size;
    vector<node_t> tree;
    vector<tag_t> lazy;

    void apply(int ql, int qr, node_t qv, int l, int r, int i) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) {
            tree[i] += qv;
            if (i < size) lazy[i] += qv;
            return;
        }
        if (lazy[i]) push(i);

        const auto m = l + r >> 1;
        apply(ql, qr, qv, l, m, lson), apply(ql, qr, qv, m, r, rson);
        pull(i);
    }
    void pull(int i) {
        tree[i] = max(tree[lson], tree[rson]);
    }
    void push(int i) {
        tree[lson] += lazy[i];
        tree[rson] += lazy[i];
        if (lson < size) lazy[lson] += lazy[i], lazy[rson] += lazy[i];
        lazy[i] = 0;
    }
#undef lson
#undef rson
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;

    vector<point> a(n);
    for (auto& [x, y, c] : a)
        cin >> x >> y >> c, --x, --y, --c;

    vector<point> vt(n << 1);
    vector<multiset<int>> psets(k);

    lazy_seg<int, int> seg(mxX);

    auto valid = [&](int mid) {
        const int len = mid + 1;
        move(a.begin(), a.end(), vt.begin());
        move(a.begin(), a.end(), vt.begin() + n);
        for (int i = n; i < n << 1; ++i)
            vt[i].x += len, vt[i].c = ~vt[i].c;

        sort(vt.begin(), vt.end(), [&](auto& a, auto& b) {
            return a.x == b.x ? a.c < b.c : a.x < b.x;
        });

        seg.clear();
        for (auto& pset : psets) pset.clear();

        for (const auto& [x, y, c] : vt) {
            auto [l, r] = pair {y, min(y + len, mxX)};
            if (c >= 0) {
                auto it = psets[c].emplace(y);
                if (it != psets[c].begin()) l = max(l, *prev(it) + len);
                if (++it != psets[c].end()) r = min(r, *it);
                if (l < r) seg.apply(l, r, 1);

                if (seg.all_prod() == k) return true;
            } else {
                auto it = psets[~c].find(y);
                if (it != psets[~c].begin()) l = max(l, *prev(it) + len);
                if (++it != psets[~c].end()) r = min(r, *it);
                if (l < r) seg.apply(l, r, -1);

                psets[~c].erase(--it);
            }
        }
        return false;
    };

    auto lo = 0, hi = mxX - 1;
    while (lo != hi) {
        const auto mid = lo + hi >> 1;
        valid(mid) ? hi = mid : lo = mid + 1;
    }
    cout << lo;
}