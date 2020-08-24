#include <cstdio>
#define loop(i,n) for(int i=0;i<n;++i)

const int mxN = 1e3;

int d[mxN], s[mxN];

int main() {
    int N, T; scanf("%d%d", &N, &T);
    loop(i, N) scanf("%d%d", d + i, s + i);

    double lo = -1000, hi = 1001000;
    loop(i, N) if (-s[i] > lo) lo = -s[i];

    while (hi - lo > 1e-8) {
        double m = (lo + hi) / 2, t = 0;
        loop(i, N) t += d[i] / (s[i] + m);
        t > T ? (lo = m) : (hi = m);
    }
    printf("%.9lf", lo);
}