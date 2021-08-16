#include <bits/stdc++.h>
using namespace std;

template <typename T>
class binary_indexed_tree {
    const size_t n;
    vector<T> tree;

public:
    binary_indexed_tree(size_t n) : n(n), tree(n + 1) {}

    // a[i] += val
    void update(size_t i, T val) {
        assert(0 <= i and i <= n);
        for (++i; i <= n; i += i & -i)
            tree[i] += val;
    }
    // sum in range [0...i)
    T query(size_t i) const {
        assert(0 <= i and i <= n);
        T ret = 0;
        for (; i; i &= i - 1)
            ret += tree[i];
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
    vector a(n, vector<int>(n));
    for (auto& vt : a) {
        for (auto& x : vt) {
            cin >> x;
        }
    }
    partial_sum(a[0].begin(), a[0].end(), a[0].begin());
    for (int i = 1; i != n; ++i) {
        a[i][0] += a[i - 1][0];
        for (int j = 1; j != n; ++j) {
            a[i][j] += max(a[i - 1][j], a[i][j - 1]);
        }
    }
    vector bits(n, binary_indexed_tree<int>(n));
    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != n; ++j) {
            bits[i].update(j, a[i][j]);
            bits[i].update(j + 1, -a[i][j]);
        }
    }
    auto sum = accumulate(a.begin(), a.end(), 0ll, [&](const auto& sum, const auto& vt) {
        return sum + accumulate(vt.begin(), vt.end(), 0ll);
    });
    vector<pair<int, int>> intervals(n);
    char op;
    for (int q = n, r, c; q--;) {
        cout << sum << '\n';
        cin >> op >> r >> c, --r, --c;
        const int x = op == 'U';
        intervals[r] = {c, n};
        if (r) {
            int ed = intervals[r].first + 1;
            while (ed != n && bits[r - 1].query(ed + 1) < bits[r].query(ed) + x) ++ed;
            intervals[r].second = ed;
        }
        int r2 = r + 1;
        for (; r2 != n; ++r2) {
            auto [st, ed] = intervals[r2 - 1];
            while (st != ed && bits[r2 - 1].query(st + 1) < bits[r2].query(st) + !x) ++st;
            if (st == ed) break;
            while (ed != n && bits[r2 - 1].query(ed + 1) < bits[r2].query(ed) + x) ++ed;
            intervals[r2] = {st, ed};
        }
        for (int i = r; i < r2; ++i) {
            sum += (intervals[i].second - intervals[i].first) * (x ? 1 : -1);
            bits[i].update(intervals[i].first, x ? 1 : -1);
            bits[i].update(intervals[i].second, x ? -1 : 1);
        }
    }
    cout << sum << '\n';
}