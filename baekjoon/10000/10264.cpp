#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
struct edge {
    int u, v;
    double w;
    edge(int u, int v, double w) : u(u), v(v), w(w) {}
};

const int mxN = 5e2;

vector<int> adj[mxN], tree[mxN * mxN];
int x[mxN], y[mxN], par[mxN * mxN];
double ans[mxN * mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    cout << fixed << setprecision(9);

    int N; cin >> N;
    loop(i, N) cin >> x[i] >> y[i];

    int M; cin >> M;
    for (int u, v; M; --M) {
        cin >> u >> v; --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<edge> e;
    loop(i, N) loop(j, N) for (int& k : adj[i]) {
        double w = min(hypot(x[i] - x[j], y[i] - y[j]), hypot(x[j] - x[k], y[j] - y[k]));
        e.emplace_back(i * N + j, k * N + j, w);
        e.emplace_back(j * N + i, j * N + k, w);
    }

    sort(e.begin(), e.end(), [&](auto & a, auto & b) {
        return a.w > b.w;
    });
    iota(par, par + N * N, 0);
    loop(i, N * N) tree[i].emplace_back(i);

    for (auto& [u, v, w] : e) {
        int pu = par[u], pv = par[v];
        if (pu == pv) continue;
        if (tree[pu].size() > tree[pv].size()) swap(pu, pv);

        for (int& x : tree[pu]) {
            int rev = x % N * N + x / N;
            if (par[rev] == pv)
                ans[x] = ans[rev] = w;
        }

        for (int& x : tree[pu]) {
            par[x] = pv;
            tree[pv].emplace_back(x);
        }

        tree[pu].clear();
    }

    int Q; cin >> Q;
    for (int u, v; Q; --Q) {
        cin >> u >> v; --u, --v;
        cout << ans[u * N + v] << '\n';
    }
    return 0;
}