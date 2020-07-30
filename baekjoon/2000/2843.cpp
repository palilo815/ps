#include <bits/stdc++.h>
using namespace std;
struct query {
    int op, u;
};

const int mx = 3e5;

int par[mx + 1], to[mx + 1], ans[mx];
bool erased[mx + 1];
query q[mx];

int _find(int u) {
    return par[u] < 0 ? u : (par[u] = _find(par[u]));
}
void _union(int i) {
    int u = _find(i), v = _find(to[i]);
    par[u] = u == v ? -2 : v;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> to[i];

    int Q; cin >> Q;
    for (int i = 0; i < Q; ++i) {
        cin >> q[i].op >> q[i].u;
        if (q[i].op == 2)
            erased[q[i].u] = true;
    }

    memset(par + 1, -1, sizeof(int) * N);
    for (int i = 1; i <= N; ++i)
        if (!erased[i] && to[i])
            _union(i);

    int j = -1;
    for (int i = Q - 1; ~i; --i) {
        if (q[i].op == 1) {
            ++j;
            int v = _find(q[i].u);
            if (par[v] ^ -2) ans[j] = v;
        }
        else _union(q[i].u);
    }

    for (; ~j; --j) {
        if (ans[j]) cout << ans[j];
        else cout << "CIKLUS";
        cout << '\n';
    }
    return 0;
}