#include <cstdio>

void solve() {
    long long N; scanf("%lld", &N);
    int l = 1, r = 141421356;
    while (l ^ r) {
        int m = l + (r - l) / 2;
        N - m * (m + 1LL) / 2 > m ? (l = m + 1) : (r = m);
    }
    printf("%d\n", l);
}
int main() {
    int T; scanf("%d", &T);
    while (T--) solve();
    return 0;
}