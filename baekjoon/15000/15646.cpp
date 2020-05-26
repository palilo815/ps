#include <iostream>
using namespace std;
typedef long long ll;

const int MAX = 5001;

int R, C;
ll fenwick[MAX][MAX];

void update(int r, int c, int v) {
    for (int i = r; i <= R; i += i & -i)
        for (int j = c; j <= C; j += j & -j)
            fenwick[i][j] += v;
}
ll read(int r, int c) {
    ll ret = 0;
    for (int i = r; i; i -= i & -i)
        for (int j = c; j; j -= j & -j)
            ret += fenwick[i][j];
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int Q; cin >> R >> C >> Q;
    while (Q--) {
        int q, r, c; cin >> q >> r >> c;
        if (q == 1) {
            int r2, c2, v; cin >> r2 >> c2 >> v;
            update(r, c, v), update(r, c2 + 1, -v);
            update(r2 + 1, c, -v), update(r2 + 1, c2 + 1, v);
        }
        else cout << read(r, c) << '\n';
    }
    return 0;
}