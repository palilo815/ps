#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

struct query_t {
    int l, r, i;
    query_t(int l, int r, int i) : l(l), r(r), i(i) {}
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int BLOCK = 512;
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    auto comp(a);
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    for (auto& x : a) {
        x = lower_bound(comp.begin(), comp.end(), x) - comp.begin();
    }
    vector<vector<query_t>> qs((n + BLOCK - 1) / BLOCK);
    for (int i = 0, l, r; i < m; ++i) {
        cin >> l >> r, --l;
        qs[l / BLOCK].emplace_back(l, r, i);
    }
    int fence = 0;
    vector<int> cnt(comp.size()), ans(m);
    for (auto& q : qs) {
        sort(q.begin(), q.end(), [&](const auto& lhs, const auto& rhs) {
            return lhs.r < rhs.r;
        });
        fence += BLOCK;
        auto ptr = fence;
        int mx = 0;
        fill(cnt.begin(), cnt.end(), 0);
        for (const auto& [l, r, id] : q) {
            for (; ptr < r; ++ptr) {
                ++cnt[a[ptr]];
                if (cnt[a[ptr]] > cnt[mx]) {
                    mx = a[ptr];
                } else if (cnt[a[ptr]] == cnt[mx]) {
                    chmax(mx, a[ptr]);
                }
            }
            const auto saved_mx = mx;
            for (int i = l, ed = min(fence, r); i < ed; ++i) {
                ++cnt[a[i]];
                if (cnt[a[i]] > cnt[mx]) {
                    mx = a[i];
                } else if (cnt[a[i]] == cnt[mx]) {
                    chmax(mx, a[i]);
                }
            }
            ans[id] = exchange(mx, saved_mx);
            for (int i = l, ed = min(fence, r); i < ed; ++i) {
                --cnt[a[i]];
            }
        }
    }
    for (const auto& x : ans) {
        cout << comp[x] << '\n';
    }
}