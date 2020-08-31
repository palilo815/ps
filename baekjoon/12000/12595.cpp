#include <cstdio>

int solve() {
    int N, ret = 0;
    for (scanf("%d", &N); N; --N) {
        int x; scanf("%d", &x);
        ret ^= x;
    }
    return ret;
}
int main() {
    int T; scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
        printf("Case #%d: %d\n", t, solve());
    return 0;
}