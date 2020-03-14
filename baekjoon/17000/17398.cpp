#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;
typedef pair<int, int> p;

const int max_N = 100000;

int parent[max_N + 1];
int cnt[max_N + 1];
p edge[max_N];
bool erased[max_N];

int _find(int u) {
    if (u == parent[u]) return u;
    return parent[u] = _find(parent[u]);
}
void _union(int u, int v) {
    parent[u] = v;
    cnt[v] += cnt[u];
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, Q; cin >> N >> M >> Q;
    loop(i, M) cin >> edge[i].first >> edge[i].second;

    stack<int> query;
    while (Q--) {
        int q; cin >> q;
        --q;
        query.emplace(q);
        erased[q] = true;
    }

    for (int i = 1; i <= N; ++i)
        parent[i] = i, cnt[i] = 1;

    loop(i, M) if (!erased[i]) {
        auto [u, v] = edge[i];
        u = _find(u), v = _find(v);
        if (u != v) _union(u, v);
    }

    ll ans = 0;
    while (!query.empty()) {
        int q = query.top(); query.pop();
        auto [u, v] = edge[q];
        u = _find(u), v = _find(v);
        if (u == v) continue;
        ans += (ll)cnt[u] * cnt[v];
        _union(u, v);
    }
    cout << ans;
    return 0;
}