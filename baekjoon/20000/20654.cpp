#include <bits/stdc++.h>
using namespace std;

struct drink {
    int d, p, l;
};

struct query {
    int64_t price, litre;
};

struct segtree {
#define lson (i << 1)
#define rson (i << 1 | 1)
    static constexpr int n = 131072;
    struct node {
        int64_t price, litre;
    };
    node tr[n << 1];

    void reset() { memset(tr, 0, sizeof(tr)); };
    void update(int p, int l) {
        for (int i = p + n; i; i >>= 1) {
            tr[i].price += int64_t(p) * l;
            tr[i].litre += l;
        }
    }
    bool query(int64_t money, int64_t need, int l = 0, int r = n, int i = 1) {
        if (tr[i].litre < need) return false;
        if (tr[i].price <= money) return true;
        if (l + 1 == r) return l * need <= money;

        int m = (l + r) >> 1;
        if (tr[lson].litre >= need)
            return query(money, need, l, m, lson);
        else if (tr[lson].price > money)
            return false;
        return query(money - tr[lson].price, need - tr[lson].litre, m, r, rson);
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

    vector<drink> a(n);
    for (auto& [d, p, l] : a)
        cin >> d >> p >> l;

    vector<query> q(m);
    for (auto& [p, l] : q)
        cin >> p >> l;

    sort(a.begin(), a.end(), [&](auto& a, auto& b) {
        return a.d > b.d;
    });

    segtree segT;
    vector<int> lo(m), hi(m, n);
    for (;;) {
        vector<vector<int>> check(m);
        bool done = true;
        for (int i = 0; i < m; ++i) {
            if (lo[i] != hi[i]) {
                done = false;
                check[(lo[i] + hi[i]) >> 1].emplace_back(i);
            }
        }
        if (done) break;

        segT.reset();
        for (int mid = 0; mid < n; ++mid) {
            segT.update(a[mid].p, a[mid].l);
            for (const auto& i : check[mid])
                segT.query(q[i].price, q[i].litre) ? hi[i] = mid : lo[i] = mid + 1;
        }
    }

    for (const auto& x : lo)
        cout << (x == n ? -1 : a[x].d) << '\n';
}