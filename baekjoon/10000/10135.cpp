#include <bits/stdc++.h>
using namespace std;

namespace std {
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template <class Fun>
class y_combinator_result {
    Fun fun_;

public:
    template <class T>
    explicit y_combinator_result(T&& fun) : fun_(std::forward<T>(fun)) {}

    template <class... Args>
    decltype(auto) operator()(Args&&... args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};

template <class Fun>
decltype(auto) y_combinator(Fun&& fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
}; // namespace std

template <typename T = int>
class BIT {
public:
    BIT(int _n) : n(_n), tree(_n + 1) {}

    void add(int i) {
        assert(0 <= i and i < n);
        for (++i; i <= n; i += i & -i)
            ++tree[i];
    }
    void del(int i) {
        assert(0 <= i and i < n);
        for (++i; i <= n; i += i & -i)
            tree[i] = 0;
    }
    T query(int i) {
        assert(0 <= i and i <= n);
        T ret = 0;
        for (; i; i &= i - 1)
            ret += tree[i];
        return ret;
    }

private:
    const int n;
    vector<T> tree;
};

struct _lamp {
    int x, y, id, k;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n;
    cin >> n;

    array<int64_t, 4> matrix;
    cin >> matrix[0] >> matrix[2] >> matrix[1] >> matrix[3];

    vector<_lamp> a(n);
    for (auto& [x, y, id, k] : a) cin >> x >> y;
    for (auto& [x, y, id, k] : a) cin >> k;
    for (int i = 0; i < n; ++i) a[i].id = i;

    int num_ys = 0;
    if (auto sign = matrix[0] * matrix[3] - matrix[1] * matrix[2]; sign == 0) {
        // two parallel vectors
        auto cross_prod = [&](int64_t x1, int64_t y1, int64_t x2, int64_t y2) -> int64_t {
            return x1 * y2 - y1 * x2;
        };

        struct relative_xy {
            int64_t x, y;
            int id;
        };

        vector<relative_xy> points(n);
        for (int i = 0; i < n; ++i) {
            points[i].x = cross_prod(a[i].x, a[i].y, matrix[0], matrix[2]);
            points[i].y = cross_prod(a[i].y, -a[i].x, matrix[0], matrix[2]);
            points[i].id = i;
        }

        sort(points.begin(), points.end(), [&](auto& lhs, auto& rhs) {
            return pair(lhs.x, lhs.y) < pair(rhs.x, rhs.y);
        });

        int64_t prv_x = LLONG_MIN;
        for (int i = n; i--;) {
            if (points[i].x != prv_x) prv_x = points[i].x, ++num_ys;
            a[points[i].id].x = i, a[points[i].id].y = num_ys - 1;
        }
    } else {
        // inverse matrix
        swap(matrix[0], matrix[3]);
        sign > 0 ? (matrix[1] = -matrix[1], matrix[2] = -matrix[2])
                 : (matrix[0] = -matrix[0], matrix[3] = -matrix[3]);

        // change basis from [[1, 0], [0, 1]] to [[X1, Y1], [X2, Y2]]
        vector<int64_t> xs(n), ys(n);
        for (int i = 0; i < n; ++i) {
            xs[i] = matrix[0] * a[i].x + matrix[1] * a[i].y;
            ys[i] = matrix[2] * a[i].x + matrix[3] * a[i].y;
        }

        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());

        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());

        for (auto& lamp : a) {
            auto x_coordinate = matrix[0] * lamp.x + matrix[1] * lamp.y,
                 y_coordinate = matrix[2] * lamp.x + matrix[3] * lamp.y;
            lamp.x = lower_bound(xs.begin(), xs.end(), x_coordinate) - xs.begin();
            lamp.y = lower_bound(ys.begin(), ys.end(), y_coordinate) - ys.begin();
        }

        num_ys = ys.size();
    }

    sort(a.begin(), a.end(), [&](auto& lhs, auto& rhs) {
        return pair(lhs.x, lhs.y) < pair(rhs.x, rhs.y);
    });

    BIT bit(num_ys);
    vector<int> ans(n), is_on(n);

    auto dnc = y_combinator([&](auto self, int lo_time, int hi_time, int lo_idx, int hi_idx) -> void {
        if (lo_time + 1 == hi_time) {
            for (int i = lo_idx; i < hi_idx; ++i)
                ans[a[i].id] = hi_time;
            return;
        }

        int mid_time = (lo_time + hi_time) >> 1;

        for (int i = lo_idx; i < hi_idx; ++i) {
            if (a[i].id < mid_time) {
                is_on[a[i].id] = 1;
                bit.add(a[i].y);
            } else if (auto cnt = bit.query(a[i].y + 1); cnt >= a[i].k) {
                is_on[a[i].id] = 1;
                bit.add(a[i].y);
            } else
                a[i].k -= cnt;
        }

        int mid_idx = stable_partition(a.begin() + lo_idx, a.begin() + hi_idx, [&](auto& lamp) {
            return is_on[lamp.id];
        }) - a.begin();

        for (int i = lo_idx; i < mid_idx; ++i) {
            is_on[a[i].id] = 0;
            bit.del(a[i].y);
        }

        if (lo_idx != mid_idx) self(lo_time, mid_time, lo_idx, mid_idx);
        if (mid_idx != hi_idx) self(mid_time, hi_time, mid_idx, hi_idx);
    });

    dnc(0, n, 0, n);

    for (const auto& x : ans)
        cout << x << ' ';
}