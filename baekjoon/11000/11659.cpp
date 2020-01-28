#include <stdio.h>

const int max_N = 100000;
int psum[max_N + 1];
int main()
{
    int n, m; scanf("%d %d", &n, &m);
    int x;
    for (int i = 1;i <= n;++i) {
        scanf("%d", &x);
        psum[i] = psum[i - 1] + x;
    }
    int a, b;
    while (m--) {
        scanf("%d %d", &a, &b);
        printf("%d\n", psum[b] - psum[a - 1]);
    }
    return 0;
}