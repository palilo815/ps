#include <bits/stdc++.h>
using namespace std;

struct query_t {
    int l, r, i;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    auto cnt = [&]() {
        auto compressed(a);
        sort(compressed.begin(), compressed.end());
        compressed.erase(unique(compressed.begin(), compressed.end()), compressed.end());
        for (auto& x : a) {
            x = lower_bound(compressed.begin(), compressed.end(), x) - compressed.begin();
        }
        return vector<int>(compressed.size());
    }();
    int m;
    cin >> m;
    vector<query_t> q(m);
    for (int i = 0; i < m; ++i) {
        cin >> q[i].l >> q[i].r, --q[i].l;
        q[i].i = i;
    }
    constexpr int BLOCK = 512;
    sort(q.begin(), q.end(), [&](const auto& lhs, const auto& rhs) {
        if (lhs.l / BLOCK != rhs.l / BLOCK) return lhs.l / BLOCK < rhs.l / BLOCK;
        return (lhs.l / BLOCK) & 1 ? lhs.r > rhs.r : lhs.r < rhs.r;
    });
    int res = 0;
    const auto add = [&](const int id) {
        if (++cnt[a[id]] == 1) ++res;
    };
    const auto del = [&](const int id) {
        if (--cnt[a[id]] == 0) --res;
    };
    vector<int> ans(m);
    int pl = q[0].l, pr = q[0].l;
    for (const auto& [l, r, i] : q) {
        while (l < pl) add(--pl);
        while (pr < r) add(pr++);
        while (pl < l) del(pl++);
        while (r < pr) del(--pr);
        ans[i] = res;
    }
    for (const auto& x : ans) {
        cout << x << '\n';
    }
}