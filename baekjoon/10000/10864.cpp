#include <stdio.h>

int F[1001];
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