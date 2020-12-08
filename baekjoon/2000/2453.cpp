#include <bits/stdc++.h>
using namespace std;

enum {
    white,
    grey,
    black
};

const int mxN = 1e4;

pair<int, int> edge[mxN];
char colour[mxN];
int par[mxN];

int find(int u) {
    return par[u] < 0 ? u : par[u] = find(par[u]);
}
void merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return;

    if (par[u] > par[v]) swap(u, v);
    par[u] += par[v];
    par[v] = u;
}
vector<int> bfs(int N, int K) {
    vector<vector<int>> adj(N);
    for (int i = 0, u, v; i < K; ++i) {
        u = find(edge[i].first);
        v = find(edge[i].second);
        if (u == v) return {};
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    queue<int> q;
    auto colouring = [&](int u) {
        pair<int, int> ret = {0, 0};
        q.emplace(u);
        colour[u] = black;
        while (!q.empty()) {
            u = q.front();
            q.pop();

            (colour[u] == black ? ret.first : ret.second) -= par[u];

            for (int& v : adj[u]) {
                if (colour[v] == colour[u]) return make_pair(-1, -1);
                if (colour[v] == white) {
                    colour[v] = colour[u] == black ? grey : black;
                    q.emplace(v);
                }
            }
        }
        return ret;
    };

    vector<int> ret;
    for (int i = 0; i < N; ++i)
        if (par[i] < 0 && colour[i] == white) {
            auto cnt = colouring(i);
            if (cnt.first == -1) return {};
            ret.emplace_back(abs(cnt.first - cnt.second));
        }
    return ret;
}
int solve() {
    int N, M, K = 0;
    cin >> N >> M;

    memset(par, -1, sizeof(int) * N);
    memset(colour, 0, N);

    for (int op, u, v; M--;) {
        cin >> op >> u >> v;
        --u, --v;
        if (op == 1)
            merge(u, v);
        else
            edge[K++] = {u, v};
    }

    auto vt = bfs(N, K);
    if (vt.empty()) return -1;

    bitset<mxN * 2 + 1> dp;
    dp[N] = true;

    for (int& x : vt)
        dp = dp >> x | dp << x;

    int ans = INT_MAX;
    for (int i = N; i <= 2 * N; ++i)
        if (dp[i]) {
            ans = min(ans, abs(N - i));
            break;
        }
    for (int i = N; ~i; --i)
        if (dp[i]) {
            ans = min(ans, abs(N - i));
            break;
        }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    for (int T = 5; T--;)
        cout << solve() << '\n';
}