#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

struct elem {
    int64_t d;
    int u;
    elem(int64_t d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<int64_t> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    int p;
    cin >> p;
    vector<vector<pair<int, int>>> adj(n);
    for (int u, v, w; p--;) {
        cin >> u >> v >> w, --u, --v;
        adj[u].emplace_back(w, v);
        a[v] += w;
    }
    priority_queue<elem> pq;
    for (int i = 0; i < n; ++i) {
        pq.emplace(a[i], i);
    }
    vector<bool> done(n);
    int64_t ans = -1;
    while (m) {
        const auto [d, u] = pq.top();
        pq.pop();
        if (done[u]) {
            continue;
        }
        --m;
        done[u] = true;
        chmax(ans, d);
        for (const auto& [w, v] : adj[u]) {
            if (!done[v]) {
                pq.emplace(a[v] -= w, v);
            }
        }
    }
    cout << ans;
}