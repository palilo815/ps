#include <bits/stdc++.h>
using namespace std;

template <typename T>
class binary_indexed_tree {
    const size_t n;
    vector<T> tree;

public:
    binary_indexed_tree(size_t n) : n(n), tree(n + 1) {}

    void update(size_t i, int val) {
        assert(0 <= i and i <= n);
        for (++i; i <= n; i += i & -i) {
            ++tree[i].first;
            tree[i].second += val;
        }
    }
    T query(size_t i) const {
        T ret {};
        for (; i; i &= i - 1) {
            ret.first += tree[i].first;
            ret.second += tree[i].second;
        }
        return ret;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (auto& [x, _] : a) cin >> x;
    for (auto& [_, y] : a) cin >> y;
    sort(a.begin(), a.end(), [&](const auto& lhs, const auto& rhs) {
        return lhs.first < rhs.first;
    });
    auto sz = [&]() {
        vector<int> comp(n);
        for (int i = 0; i < n; ++i) {
            comp[i] = a[i].second;
        }
        sort(comp.begin(), comp.end());
        comp.erase(unique(comp.begin(), comp.end()), comp.end());
        for (auto& [_, y] : a) {
            y = lower_bound(comp.begin(), comp.end(), y) - comp.begin();
        }
        return comp.size();
    }();
    binary_indexed_tree<pair<int, int64_t>> bit(sz);
    int64_t ans = 0;
    for (auto it = a.begin(), jt = it; it != a.end(); it = jt) {
        jt = find_if_not(it, a.end(), [&](const auto& x) {
            return x.first == it->first;
        });
        for_each(it, jt, [&](auto& x) {
            const auto res = bit.query(x.second);
            x.first = res.first;
            ans += res.second;
        });
        for_each(it, jt, [&](const auto& x) {
            bit.update(x.second, x.first);
        });
    }
    cout << ans;
}