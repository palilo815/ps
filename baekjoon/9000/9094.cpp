#include <stdio.h>

int main()
{
    int t, n, m;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        int ans = 0;
        for (int a = 1; a < n; ++a)
            for (int b = a + 1; b < n; ++b)
                if ((a * a + b * b + m) % (a * b) == 0) ++ans;
        printf("%d\n", ans);
    }
    return 0;
}