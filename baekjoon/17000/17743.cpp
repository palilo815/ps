#include <bits/stdc++.h>
using namespace std;

class segtree {
    const int n;
    vector<int> tree, cnt;

public:
    segtree(int _n) : n(_n), tree(1 << (n + 1)), cnt(n + 1) {
        for (int i = 0; i <= n; ++i)
            cnt[i] = 1 << i;
    }

    int& operator[](int i) { return cnt[i]; }
    void flip(int i) {
        int val = tree[i += 1 << n] ? -1 : 1;
        for (int d = n; i; i >>= 1, --d) {
            if (tree[i] == 0 || tree[i] == 1 << (n - d)) --cnt[d];
            tree[i] += val;
            if (tree[i] == 0 || tree[i] == 1 << (n - d)) ++cnt[d];
        }
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, q;
    cin >> n >> q;

    int64_t total = 0; // # of nodes
    for (int i = 0; i <= n; ++i)
        total += 1ll * (1 << i) * (1 << i);

    segtree row(n), col(n);

    for (int i; q--;) {
        char c;
        cin >> c >> i, --i;
        (c == '0' ? row : col).flip(i);

        int64_t grey = total;
        for (int i = 0; i <= n; ++i)
            grey -= 1ll * row[i] * col[i];
        cout << grey * 4 + 1 << '\n';
    }
}