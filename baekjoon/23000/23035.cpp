#include <bits/stdc++.h>
using namespace std;

template <typename T>
class binary_indexed_tree {
    const size_t n;
    vector<T> tree;

public:
    binary_indexed_tree(size_t n) : n(n), tree(n + 1) {}

    void update(size_t i, T val) {
        assert(0 <= i and i <= n);
        for (++i; i <= n; i += i & -i) {
            chmax(tree[i], val);
        }
    }
    T query(size_t i) const {
        assert(0 <= i and i <= n);
        T ret = 0;
        for (; i; i &= i - 1) {
            chmax(ret, tree[i]);
        }
        return ret;
    }

private:
    void chmax(T& _old, T _new) const {
        if (_new > _old) {
            _old = _new;
        }
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, t;
    cin >> n >> m >> t;
    vector<pair<int, int>> a(t);
    for (auto& [x, y] : a) {
        cin >> x >> y;
    }
    a.erase(remove_if(a.begin(), a.end(), [&](const auto& cat) {
        return cat.first > n || cat.second > m;
    }),
        a.end());
    auto sz = [&](auto& container) {
        vector<int> comp(container.size());
        transform(container.begin(), container.end(), comp.begin(), [&](const auto& x) {
            return x.second;
        });
        sort(comp.begin(), comp.end());
        comp.erase(unique(comp.begin(), comp.end()), comp.end());
        for_each(container.begin(), container.end(), [&](auto& x) {
            x.second = lower_bound(comp.begin(), comp.end(), x.second) - comp.begin();
        });
        return comp.size();
    }(a);
    binary_indexed_tree<int> bit(sz);
    sort(a.begin(), a.end());
    for (const auto& [_, y] : a) {
        bit.update(y, bit.query(y + 1) + 1);
    }
    cout << bit.query(sz);
}