#include <cstdio>

const int mxN = 500;

int a[mxN];

int main() {
    int N, M; scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; ++i)
        scanf("%d", a + i);

    double ans = 0;
    for (int u, v, w; M; --M) {
        scanf("%d%d%d", &u, &v, &w);
        double tmp = (a[u] + a[v]) / (double)w;
        if (tmp > ans)
            ans = tmp;
    }
    printf("%.6lf", ans);
    return 0;
}