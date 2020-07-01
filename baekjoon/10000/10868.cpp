#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 100000;

int sparse[17][max_N];

int query(int l, int r) {
    int k = 31 - __builtin_clz(r - l);
    return min(sparse[k][l], sparse[k][r - (1 << k)]);
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    int R = 31 - __builtin_clz(N);

    for (int i = 0; i < N; ++i)
        cin >> sparse[0][i];
    for (int i = 1; i <= R; ++i)
        for (int j = 0; j + (1 << i) <= N; ++j)
            sparse[i][j] = min(sparse[i - 1][j], sparse[i - 1][j + (1 << (i - 1))]);

    while (M--) {
        int l, r; cin >> l >> r;
        cout << query(l - 1, r) << '\n';
    }
    return 0;
}