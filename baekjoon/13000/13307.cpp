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

struct point {
    int x, y, id;
    point() = default;
    point(int _x, int _y, int _id) : x(_x), y(_y), id(_id) {}

    using P = point;

    bool operator<(const P& p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(const P& p) const { return id == p.id; }

    int64_t cross(const P& a, const P& b) const { return int64_t(a.x - x) * (b.y - y) - int64_t(a.y - y) * (b.x - x); }
};

vector<point> convex_hull(vector<point> pts) {
    sort(pts.begin(), pts.end());
    vector<point> hull(pts.size() + 1);
    int s = 0, t = 0;
    for (int it = 2; it--; s = --t, reverse(pts.begin(), pts.end()))
        for (const auto& p : pts) {
            while (t >= s + 2 && hull[t - 2].cross(hull[t - 1], p) <= 0) t--;
            hull[t++] = p;
        }
    return {hull.begin(), hull.begin() + t - (t == 2 && hull[0] == hull[1])};
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n;
    cin >> n;

    vector<point> a(3 * n);
    for (int i = 0; i < n; ++i)
        cin >> a[i].x >> a[i].y, a[i].id = ~i;
    for (int i = n; i < 3 * n; ++i)
        cin >> a[i].x >> a[i].y, a[i].id = i - n;

    vector<pair<int, int>> ans(n);
    y_combinator([&](auto self, auto st, auto ed) -> void {
        if (st == ed) return;
        if (ed - st == 3) {
            swap(*st, *find_if(st, ed, [&](const auto& x) { return x.id < 0; }));
            ans[~st->id] = {(st + 1)->id, (st + 2)->id};
            return;
        }

        auto hull = convex_hull({st, ed});
        point pivot;
        bool is_blue; // pivot is blue?
        if (auto it = find_if(hull.begin(), hull.end(), [&](const auto& x) { return x.id < 0; }); it == hull.end())
            pivot = hull.front(), is_blue = false;
        else
            pivot = *it, is_blue = true;

        swap(*st, *find(st, ed, pivot));
        sort(st + 1, ed, [&](const auto& lhs, const auto& rhs) {
            return st->cross(lhs, rhs) > 0;
        });

        int sum = 0;
        if (is_blue) {
            vector<point>::iterator r;
            for (auto it = st; it != ed; ++it) {
                if (it->id < 0) sum += 2;
                else {
                    --sum;
                    if (sum == 1) r = prev(it);
                    if (sum == 0) {
                        swap(*st, *r);
                        self(st, r), self(r, it + 1), self(it + 1, ed);
                        return;
                    }
                }
            }
        } else {
            for (auto it = st; it != ed - 1; ++it) {
                sum += it->id < 0 ? 2 : -1;
                if (sum == 0) {
                    self(st, it + 1), self(it + 1, ed);
                    return;
                }
            }
            sum = -1;
            for (auto it = ed - 1; it != st; --it) {
                sum += it->id < 0 ? 2 : -1;
                if (sum == 0) {
                    swap(*st, *prev(it));
                    self(st, it - 1), self(it - 1, ed);
                    return;
                }
            }
        }
        assert(false);
    })(a.begin(), a.end());

    for (const auto& [i, j] : ans)
        cout << i + 1 << ' ' << j + 1 << '\n';
}