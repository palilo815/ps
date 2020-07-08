#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define x first
#define y second
using namespace std;
using p = pair<int, int>;

const int max_N = 100000;
const size_t LEN = 131072;

p a[max_N];
int table[17][LEN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    loop(i, N) {
        cin >> a[i].x;
        a[i].y = i;
    }

    int L = 1, D = -1;
    while (L < N) L <<= 1, ++D;

    sort(a, a + N);
    loop(i, N) table[0][i] = a[i].y;
    memset(table[0] + N, 0x3f, sizeof(int) * (L - N));

    for (int d = 0, k = 1; d < D; ++d, k <<= 1)
        for (int* t = table[d]; t < table[d] + L; t += k << 1)
            merge(t, t + k, t + k, t + k * 2, t + LEN);

    while (M--) {
        int i, j, k, d = D, l = 0, r = L; cin >> i >> j >> k;
        for (--i, --j, --k; d >= 0; --d) {
            int m = (l + r) >> 1;
            int cnt = upper_bound(table[d] + l, table[d] + m, j) -
                      lower_bound(table[d] + l, table[d] + m, i);
            k >= cnt ? (l = m, k -= cnt) : (r = m);
        }
        cout << a[l].x << '\n';
    }
    return 0;
}