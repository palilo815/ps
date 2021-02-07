#include <bits/stdc++.h>
using namespace std;

constexpr int mxK = 100000;
constexpr int sqmxK = 317;

struct query {
    int l, r, k, id;
};

struct BIT {
    int tr[mxK + 1];
    BIT() {
        memset(tr + 1, 0, sizeof(int) * mxK);
    }
    void add(int i) {
        for (; i <= mxK; i += i & -i)
            ++tr[i];
    }
    void sub(int i) {
        for (; i <= mxK; i += i & -i)
            --tr[i];
    }
    int query(int i) const {
        int ret = 0;
        for (; i; i -= i & -i)
            ret += tr[i];
        return ret;
    }
    int query(int l, int r) const {
        return query(r) - query(l);
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<int> a(n), b(n);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;

    int m;
    cin >> m;

    vector<query> q(m);
    for (int i = 0; i < m; ++i) {
        cin >> q[i].l >> q[i].r >> q[i].k;
        --q[i].l, q[i].id = i;
    }

    const int sq = sqrt(n - 1) + 1;
    sort(q.begin(), q.end(), [&](auto& a, auto& b) {
        if (a.l / sq != b.l / sq) return a.l < b.l;
        return a.l / sq & 1 ? a.r > b.r : a.r < b.r;
    });

    BIT bitA, bitB;
    int cntA[sqmxK] {}, cntB[sqmxK] {};

    auto add = [&](int i) {
        bitA.add(a[i]), bitB.add(b[i]);
        if (a[i] < sqmxK) ++cntA[a[i]];
        if (b[i] < sqmxK) ++cntB[b[i]];
    };
    auto sub = [&](int i) {
        bitA.sub(a[i]), bitB.sub(b[i]);
        if (a[i] < sqmxK) --cntA[a[i]];
        if (b[i] < sqmxK) --cntB[b[i]];
    };

    vector<int64_t> ans(m);
    int pl = 0, pr = 0;
    for (const auto [l, r, k, id] : q) {
        while (l < pl) add(--pl);
        while (pr < r) add(pr++);
        while (pl < l) sub(pl++);
        while (r < pr) sub(--pr);

        const int sqK = sqrt(k);

        int64_t res = 0;
        for (int x = 1; x <= sqK; ++x) {
            res += int64_t(cntA[x]) * bitB.query(k / x);
            res += int64_t(cntB[x]) * bitA.query(sqK, k / x);
        }
        ans[id] = res;
    }

    for (const auto x : ans)
        cout << x << '\n';
}