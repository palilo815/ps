#include <bits/stdc++.h>
using namespace std;

template <typename key_t, typename value_t>
struct min_heap_elem {
    key_t key;
    value_t value;

    min_heap_elem() = default;
    min_heap_elem(const key_t& key, const value_t& value) : key(key), value(value) {}

    bool operator<(const min_heap_elem& rhs) const {
        return key > rhs.key;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int INF = 0x3f3f3f3f;
    int n;
    cin >> n;
    vector<int> pref(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> pref[i];
    }
    partial_sum(next(pref.begin()), pref.end(), next(pref.begin()));
    vector<bool> is_first(pref.back() + 1);
    for (const auto& x : pref) {
        is_first[x] = true;
    }
    int m;
    cin >> m;
    vector transfer(pref.back(), -1);
    for (int p1, p2, q1, q2; m--;) {
        cin >> p1 >> p2 >> q1 >> q2, --p1, --p2, --q1, --q2;
        transfer[pref[p1] + p2] = pref[q1] + q2;
        transfer[pref[q1] + q2] = pref[p1] + p2;
    }
    priority_queue<min_heap_elem<int, int>> pq;
    vector<int> dist(pref.back());
    auto dijk = [&](const int s, const int t, const int cost) -> int {
        fill(dist.begin(), dist.end(), INF);
        pq.emplace(dist[s] = 0, s);
        while (!pq.empty()) {
            const auto [d, u] = pq.top();
            pq.pop();
            if (d != dist[u]) continue;
            if (!is_first[u] && dist[u - 1] > d + 1) {
                pq.emplace(dist[u - 1] = d + 1, u - 1);
            }
            if (!is_first[u + 1] && dist[u + 1] > d + 1) {
                pq.emplace(dist[u + 1] = d + 1, u + 1);
            }
            if (const auto v = transfer[u];
                ~v && dist[v] > d + cost) {
                pq.emplace(dist[v] = d + cost, v);
            }
        }
        return dist[t];
    };
    cin >> m;
    for (int t, u, u2, v, v2; m--;) {
        cin >> t >> u >> u2 >> v >> v2, --u, --u2, --v, --v2;
        u = pref[u] + u2, v = pref[v] + v2;
        cout << dijk(u, v, t) << '\n';
    }
}