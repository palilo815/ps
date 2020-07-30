#include <bits/stdc++.h>
using namespace std;

const int mxN = 4e6 + 2;

int par[mxN];

int _find(int u) {
    return ~par[u] ? (par[u] = _find(par[u])) : u;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M, K; cin >> N >> M >> K;
    while (M--) {
        int x; cin >> x;
        par[x] = -1;
    }
    par[N + 1] = -1;

    for (int i = N, nxt = N + 1; ~i; --i)
        par[i] ? (nxt = i) : (par[i] = nxt);

    while (K--) {
        int x; cin >> x;
        cout << (x = _find(x + 1)) << '\n';
        par[x] = _find(x + 1);
    }
    return 0;
}