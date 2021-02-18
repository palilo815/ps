#include <bits/stdc++.h>
using namespace std;

struct BIT {
    vector<int> tree;
    int n;

    BIT(int n) : tree(n + 1), n(n) {}
    void update(int i) {
        for (++i; i <= n; i += i & -i)
            ++tree[i];
    }
    int query(int i) {
        int ret = 0;
        for (; i; i -= i & -i)
            ret += tree[i];
        return ret;
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

    vector<int> a(n);
    for (auto& x : a) cin >> x, --x;

    int first_sorted = 0;
    for (int i = n - 1; i; --i)
        if (a[i - 1] > a[i]) {
            first_sorted = i;
            break;
        }

    BIT bit(n);
    for (int i = first_sorted; i < n; ++i)
        bit.update(a[i]);

    cout << first_sorted << '\n';
    for (int i = 0; i < first_sorted; ++i) {
        cout << first_sorted - i - 1 + bit.query(a[i]) << ' ';
        bit.update(a[i]);
    }
}