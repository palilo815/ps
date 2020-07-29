#include <bits/stdc++.h>
using namespace std;
struct query {
    int u, v;
};

const int mxN = 2e5;
const string s[2] = {"NO\n", "YES\n"};

int par[mxN + 1], parent[mxN + 1];
query q[(mxN << 1) - 1];
char ans[mxN];

int _find(int u) {
    return ~parent[u] ? (parent[u] = _find(parent[u])) : u;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, Q; cin >> N >> Q;
    for (int i = 2; i <= N; ++i)
        cin >> par[i];
    memset(parent + 1, -1, sizeof(int) * N);

    for (int i = 0; i < Q + N - 1; ++i) {
        cin >> q[i].u >> q[i].v;
        if (q[i].u) cin >> q[i].u;
    }

    for (int i = Q + N - 2, j = Q; ~i; --i)
        q[i].u ? (ans[--j] = _find(q[i].u) == _find(q[i].v)) : (parent[_find(q[i].v)] = _find(par[q[i].v]));

    for (int i = 0; i < Q; ++i)
        cout << s[ans[i]];
    return 0;
}