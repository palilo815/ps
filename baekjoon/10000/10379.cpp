#include <bits/stdc++.h>
using namespace std;

struct point {
    int x, y, z;
    bool operator==(const point& rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }
};

struct triangle {
    point p1, p2, p3;
};

struct elem {
    int d, u;
    elem(int d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
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

    vector<triangle> a(n);
    for (auto& [p1, p2, p3] : a) {
        cin >> p1.x >> p1.y >> p1.z;
        cin >> p2.x >> p2.y >> p2.z;
        cin >> p3.x >> p3.y >> p3.z;
    }

    point src, dst;
    cin >> src.x >> src.y >> src.z;
    cin >> dst.x >> dst.y >> dst.z;

    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (a[i].p1 == a[j].p1 || a[i].p1 == a[j].p2 || a[i].p1 == a[j].p3)
                adj[i].emplace_back(a[i].p1.z, j), adj[j].emplace_back(a[i].p1.z, i);
            if (a[i].p2 == a[j].p1 || a[i].p2 == a[j].p2 || a[i].p2 == a[j].p3)
                adj[i].emplace_back(a[i].p2.z, j), adj[j].emplace_back(a[i].p2.z, i);
            if (a[i].p3 == a[j].p1 || a[i].p3 == a[j].p2 || a[i].p3 == a[j].p3)
                adj[i].emplace_back(a[i].p3.z, j), adj[j].emplace_back(a[i].p3.z, i);
        }
    }

    auto sign = [&](point p1, point p2, point p3) {
        return int64_t(p1.x - p3.x) * (p2.y - p3.y) - int64_t(p2.x - p3.x) * (p1.y - p3.y);
    };
    auto point_in_triangle = [&](point p, triangle t) {
        auto d1 = sign(p, t.p1, t.p2);
        auto d2 = sign(p, t.p2, t.p3);
        auto d3 = sign(p, t.p3, t.p1);

        auto pos = d1 > 0 || d2 > 0 || d3 > 0;
        auto neg = d1 < 0 || d2 < 0 || d3 < 0;
        return !(pos && neg);
    };

    int src_idx = -1, dst_idx = -1;
    for (int i = 0; i < n; ++i) {
        if (src_idx == -1 && point_in_triangle(src, a[i])) src_idx = i;
        if (dst_idx == -1 && point_in_triangle(dst, a[i])) dst_idx = i;
    }

    vector<int> height(n, 0x3f3f3f3f);
    vector<int> par(n, -1);

    priority_queue<elem> pq;
    pq.emplace(height[src_idx] = src.z, src_idx);

    for (;;) {
        const auto [h, u] = pq.top();
        pq.pop();
        if (h != height[u]) continue;
        if (u == dst_idx) break;

        for (const auto& [w, v] : adj[u])
            if (height[v] > max(w, height[u])) {
                pq.emplace(height[v] = max(w, height[u]), v);
                par[v] = u;
            }
    }

    vector<point> path = {dst};
    for (int i = dst_idx; ~par[i]; i = par[i]) {
        point via = {0, 0, INT_MAX};
        if (via.z > a[i].p1.z && (a[i].p1 == a[par[i]].p1 || a[i].p1 == a[par[i]].p2 || a[i].p1 == a[par[i]].p3))
            via = a[i].p1;
        if (via.z > a[i].p2.z && (a[i].p2 == a[par[i]].p1 || a[i].p2 == a[par[i]].p2 || a[i].p2 == a[par[i]].p3))
            via = a[i].p2;
        if (via.z > a[i].p3.z && (a[i].p3 == a[par[i]].p1 || a[i].p3 == a[par[i]].p2 || a[i].p3 == a[par[i]].p3))
            via = a[i].p3;
        path.emplace_back(via);
    }
    path.emplace_back(src);
    reverse(path.begin(), path.end());

    cout << path.size() << '\n';
    for (const auto& [x, y, z] : path)
        cout << x << ' ' << y << ' ' << z << '\n';
}