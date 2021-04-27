#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct BIT {
    BIT(int _n) : n(_n), tree(_n + 1) {}
    void update(int i, T val) {
        for (++i; i <= n; i += i & -i)
            tree[i] = max(tree[i], val);
    }
    T query(int r) {
        T ret = 0;
        for (; r; r &= r - 1)
            ret = max(ret, tree[r]);
        return ret;
    }

private:
    const int n;
    vector<T> tree;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, p;
    cin >> n >> p;

    vector<tuple<int, int, int>> a(p << 1);
    vector<int> dp(p);
    for (int i = 0; i < p; ++i) {
        cin >> get<0>(a[i << 1]) >> get<1>(a[i << 1]);
        cin >> get<0>(a[i << 1 | 1]) >> get<1>(a[i << 1 | 1]);

        get<2>(a[i << 1]) = ~i, get<2>(a[i << 1 | 1]) = i;
        dp[i] = (get<0>(a[i << 1 | 1]) - get<0>(a[i << 1])) +
                (get<1>(a[i << 1 | 1]) - get<1>(a[i << 1]));
    }

    // compress y-coordinates
    vector<int> ord(p << 1);
    for (int i = 0; i < p << 1; ++i)
        ord[i] = get<1>(a[i]);
    sort(ord.begin(), ord.end());
    ord.erase(unique(ord.begin(), ord.end()), ord.end());

    for (auto& [x, y, i] : a)
        y = lower_bound(ord.begin(), ord.end(), y) - ord.begin();
    sort(a.begin(), a.end());

    BIT<int> bit(ord.size());
    for (const auto& [x, y, i] : a)
        if (i < 0)
            dp[~i] += bit.query(y + 1);
        else
            bit.update(y, dp[i]);
    cout << (n << 1) - bit.query(ord.size());
}