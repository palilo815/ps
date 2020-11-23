#include <bits/stdc++.h>
using namespace std;
using pli = pair<int64_t, int>;

const int mxN = 2e5;

vector<pli> adj[mxN];
pli vtx[mxN + 1];
int N, t, in[mxN], out[mxN], bit[mxN + 1], ans[mxN];

void dfs(int u) {
    in[u] = t++;
    int64_t d = vtx[u].first;
    for (auto& [w, v] : adj[u]) {
        vtx[v] = {d + w, v};
        dfs(v);
    }
    out[u] = t;
}
void update(int u) {
    for (int i = in[u] + 1; i <= N; i += i & -i)
        ++bit[i];
}
void query(int u) {
    int cnt = 0;
    for (int i = in[u]; i; i -= i & -i)
        cnt -= bit[i];
    for (int i = out[u]; i; i -= i & -i)
        cnt += bit[i];
    ans[u] = cnt;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int64_t L;
    cin >> N >> L;

    for (int u = 1, p; u < N; ++u) {
        int64_t d;
        cin >> p >> d;
        adj[p - 1].emplace_back(d, u);
    }

    dfs(0);

    sort(vtx, vtx + N, [&](auto& a, auto& b) {
        return a.first < b.first;
    });
    vtx[N].first = LLONG_MAX; // sentinel

    for (int l = 0, r = 0; l < N; ++l) {
        while (vtx[r].first - vtx[l].first <= L) update(vtx[r++].second);
        query(vtx[l].second);
    }

    for (int i = 0; i < N; ++i)
        cout << ans[i] << '\n';
}