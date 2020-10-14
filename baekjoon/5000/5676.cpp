#include <bits/stdc++.h>
#define left (i << 1)
#define right (i << 1 | 1)
using namespace std;

const int mxN = 1e5;

char segT[mxN << 1];

void update(int i, int val) {
    segT[i] = val ? val > 0 ? '+' : '-' : 0;
    while (i >>= 1)
        segT[i] = segT[left] && segT[right] ? segT[left] == segT[right] ? '+' : '-' : 0;
}
void query(int l, int r) {
    char ret = '+';
    for (; l != r; l >>= 1, r >>= 1) {
        if (l & 1) {
            if (segT[l]) ret = ret == segT[l] ? '+' : '-';
            else {
                cout << 0;
                return;
            }
            ++l;
        }
        if (r & 1) {
            --r;
            if (segT[r]) ret = ret == segT[r] ? '+' : '-';
            else {
                cout << 0;
                return;
            }
        }
    }
    cout << ret;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    for (int N, K; cin >> N >> K; cout << '\n') {
        memset(segT, 0, N << 1);
        for (int i = 0, x; i < N; ++i) {
            cin >> x;
            if (x) segT[i + N] = x > 0 ? '+' : '-';
        }

        for (int i = N - 1; i; --i)
            if (segT[left] && segT[right])
                segT[i] = segT[left] == segT[right] ? '+' : '-';

        for (int a, b; K--;) {
            char q;
            cin >> q >> a >> b;
            q == 'C' ? update(a - 1 + N, b) : query(a - 1 + N, b + N);
        }
    }
    return 0;
}