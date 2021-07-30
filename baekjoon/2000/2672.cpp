#include <bits/stdc++.h>
using namespace std;

template <typename T>
class sweep_line {
    const int n;
    vector<T> tree, len;
    vector<int> cnt;

public:
    sweep_line(const vector<T>& compressed) : n(compressed.size()), tree(n << 1), len(n << 1), cnt(n << 1) {
        for (int i = 0; i < n - 1; ++i) len[i + n] = compressed[i + 1] - compressed[i];
        for (int i = n - 1; i; --i) len[i] = len[i << 1] + len[i << 1 | 1];
    }
    void update(int l, int r, int v) {
        l += n, r += n;
        const int l0 = l, r0 = r;
        for (; l != r; l >>= 1, r >>= 1) {
            if (l & 1) apply(l++, v);
            if (r & 1) apply(--r, v);
        }
        tree[l0] = cnt[l0] ? len[l0] : 0;
        tree[r0] = cnt[r0] ? len[r0] : 0;
        for (int i = l0 >> 1; i; i >>= 1)
            tree[i] = cnt[i] ? len[i] : tree[i << 1] + tree[i << 1 | 1];
        for (int i = r0 >> 1; i; i >>= 1)
            tree[i] = cnt[i] ? len[i] : tree[i << 1] + tree[i << 1 | 1];
    }
    T get_sum() const { return tree[1]; }

private:
    void apply(int i, int v) {
        tree[i] = (cnt[i] += v) ? len[i] : (i < n ? tree[i << 1] + tree[i << 1 | 1] : 0);
    }
};

struct line_t {
    int x1, x2, y, v;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<line_t> a(n << 1);
    vector<int> x_vals(n << 1);
    for (int i = 0; i < n << 1; i += 2) {
        double x, y, w, h;
        cin >> x >> y >> w >> h;
        const int x1 = x * 10, y1 = y * 10;
        const int x2 = x1 + w * 10, y2 = y1 + h * 10;
        a[i] = {x1, x2, y1, 1};
        a[i | 1] = {x1, x2, y2, -1};
        x_vals[i] = x1, x_vals[i | 1] = x2;
    }
    sort(x_vals.begin(), x_vals.end());
    x_vals.erase(unique(x_vals.begin(), x_vals.end()), x_vals.end());
    for (auto& [x1, x2, y, v] : a) {
        x1 = lower_bound(x_vals.begin(), x_vals.end(), x1) - x_vals.begin();
        x2 = lower_bound(x_vals.begin() + x1 + 1, x_vals.end(), x2) - x_vals.begin();
    }
    sort(a.begin(), a.end(), [&](const auto& lhs, const auto& rhs) {
        return lhs.y < rhs.y;
    });
    sweep_line sweep(x_vals);
    int ans = 0, prv_y = a.front().y;
    for (const auto& [x1, x2, y, v] : a) {
        ans += sweep.get_sum() * (y - exchange(prv_y, y));
        sweep.update(x1, x2, v);
    }
    cout << ans / 100;
    if (ans % 100) {
        cout << '.' << ans / 10 % 10 << ans % 10;
    }
}