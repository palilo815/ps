#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 4e6;

int a[mxN], par[mxN + 1];

int _find(int u) {
    return ~par[u] ? (par[u] = _find(par[u])) : u;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M, K; cin >> N >> M >> K;
    loop(i, M) cin >> a[i];

    sort(a, a + M);
    memset(par, -1, sizeof(int) * (M + 1));

    loop(i, K) {
        int x; cin >> x;
        x = _find(upper_bound(a, a + M, x) - a);
        cout << a[x] << '\n';
        par[x] = _find(x + 1);
    }
    return 0;
}