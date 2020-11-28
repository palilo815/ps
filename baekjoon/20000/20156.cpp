#include <bits/stdc++.h>
using namespace std;

struct query {
    int A, B, C, i;
    query(int A = 0, int B = 0, int C = 0, int i = 0) : A(A), B(B), C(C), i(i) {}
};

struct disjoint_set {
    vector<int> par;
    disjoint_set(int n) {
        par = vector<int>(n, -1);
    }
    int find(int u) {
        return par[u] < 0 ? u : (par[u] = find(par[u]));
    }
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;

        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M, K;
    cin >> N >> M >> K;

    vector<int> mentor(N + 1);
    for (int i = 1; i <= N; ++i)
        cin >> mentor[i];

    vector<int> X(M + 1);
    for (int i = 1; i <= M; ++i)
        cin >> X[i];

    vector<bool> broken(N + 1);
    for (int i = 1; i <= M; ++i) {
        if (broken[X[i]]) X[i] = 0;
        broken[X[i]] = true;
    }

    vector<query> q(K);
    {
        int j = 0;
        for (auto& [A, B, C, i] : q) {
            cin >> A >> B >> C;
            i = j++;
        }
    }

    sort(q.begin(), q.end(), [&](auto& a, auto& b) {
        return a.A > b.A;
    });
    q.emplace_back(-1, -1, -1, -1);

    disjoint_set dsu(N + 1);
    for (int i = 1; i <= N; ++i)
        if (!broken[i] && ~mentor[i])
            dsu.merge(i, mentor[i]);

    vector<bool> ans(K);
    for (int i = M, j = 0; ~i; --i) {
        for (; q[j].A == i; ++j)
            ans[q[j].i] = dsu.find(q[j].B) == dsu.find(q[j].C);
        if (~mentor[X[i]]) dsu.merge(X[i], mentor[X[i]]);
    }

    for (auto x : ans)
        cout << (x ? "Same Same;\n" : "No;\n");
}