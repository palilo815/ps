#include <stdio.h>

int main()
{
    int n;
    while (1) {
        scanf("%d", &n);
        if (n == 0) break;
        int ans = n;
        while (n != 1) {
            if (n % 2) n = 3 * n + 1;
            else n /= 2;
            if (n > ans) ans = n;
        }
        printf("%d\n", ans);
    }
    return 0;
}