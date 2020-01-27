#include <stdio.h>

const int max_N = 100000;
int F[max_N + 1];
int main()
{
    int n, m; scanf("%d %d", &n, &m);
    while (m--) {
        int a, b; scanf("%d %d", &a, &b);
        ++F[a], ++F[b];
    }
    for (int i = 1; i <= n; ++i)
        printf("%d\n", F[i]);
    return 0;
}