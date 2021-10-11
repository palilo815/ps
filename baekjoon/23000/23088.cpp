#include <bits/stdc++.h>
using namespace std;

struct info_t {
    int t, p, b;
};

struct heap_elem {
    int p, b, id;

    heap_elem() = default;
    heap_elem(int p, int b, int id) : p(p), b(b), id(id) {}

    bool operator<(const heap_elem& rhs) const {
        if (p != rhs.p) return p < rhs.p;
        if (b != rhs.b) return b > rhs.b;
        return id > rhs.id;
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
    vector<info_t> a(n);
    for (auto& [t, p, b] : a) {
        cin >> t >> p >> b;
    }
    int cur = a.front().t;
    priority_queue<heap_elem> pq;
    for (int i = 0;;) {
        for (; i != n && a[i].t <= cur; ++i) {
            pq.emplace(a[i].p - a[i].t, a[i].b, i);
        }
        if (i == n) break;
        for (; !pq.empty() && cur < a[i].t; pq.pop()) {
            cout << pq.top().id + 1 << ' ';
            cur += pq.top().b;
        }
        if (cur < a[i].t) cur = a[i].t;
    }
    for (; !pq.empty(); pq.pop()) {
        cout << pq.top().id + 1 << ' ';
    }
}