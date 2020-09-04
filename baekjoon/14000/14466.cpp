#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 100;

bool b[mxN][mxN][2];
int par[mxN * mxN];

int _find(int u) {
    return ~par[u] ? (par[u] = _find(par[u])) : u;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, K, R; cin >> N >> K >> R;
    for (int r1, c1, r2, c2, d1, d2; R; --R) {
        cin >> r1 >> c1 >> r2 >> c2;
        if (r1 > r2) swap(r1, r2);
        else if (c1 > c2) swap(c1, c2);
        b[r1 - 1][c1 - 1][r1 < r2] = true;
    }

    memset(par, -1, sizeof(par));
    loop(i, N) loop(j, N) {
        if (j + 1 != N && !b[i][j][0]) {
            int u = _find(i * N + j), v = _find(i * N + j + 1);
            if (u ^ v) par[u] = v;
        }
        if (i + 1 != N && !b[i][j][1]) {
            int u = _find(i * N + j), v = _find((i + 1) * N + j);
            if (u ^ v) par[u] = v;
        }
    }

    unordered_map<int, int> cnt;
    int ans = 0;
    loop(i, K) {
        int r, c; cin >> r >> c; --r, --c;
        int id = _find(r * N + c);
        ans += i - cnt[id]++;
    }
    cout << ans;
    return 0;
}