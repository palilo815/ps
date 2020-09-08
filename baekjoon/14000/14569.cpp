#include <cstdio>
using ll = long long;

const int mxN = 1e3;

ll a[mxN];

int main() {
    int N; scanf("%d", &N);
    for (int i = 0, m, x; i < N; ++i) {
        for (scanf("%d", &m); m--;) {
            scanf("%d", &x);
            a[i] |= 1LL << x;
        }
    }

    int M; scanf("%d", &M);
    for (int m, x; M; --M) {
        ll mask = 0;
        for (scanf("%d", &m); m--;) {
            scanf("%d", &x);
            mask |= 1LL << x;
        }

        int ans = 0;
        for (int i = 0; i < N; ++i)
            if ((mask & a[i]) == a[i])
                ++ans;
        printf("%d\n", ans);
    }
    return 0;
}