#include <cstdio>

unsigned solve(unsigned m) {
    return m - m / 3u - m / 5u + m / 15u;
}
int main() {
    unsigned N, l = 1, r = -2, m;
    scanf("%u", &N);
    while (l ^ r) {
        m = (l + r) >> 1;
        solve(m) < N ? (l = m + 1) : (r = m);
    }
    printf("%u", l);
    return 0;
}