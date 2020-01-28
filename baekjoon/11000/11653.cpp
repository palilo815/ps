#include <stdio.h>

int main()
{
    int n; scanf("%d", &n);
    int mod = 2;
    while (n > 1) {
        while (n % mod == 0) {
            n /= mod;
            printf("%d\n", mod);
        }
        ++mod;
    }
    return 0;
}