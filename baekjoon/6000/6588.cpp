#include <stdio.h>

bool sieve[1000000];
int main()
{
    sieve[0] = sieve[1] = true;
    for (int i = 2;i < 1000000;++i)
        if (!sieve[i])
            for (int j = i * 2;j < 1000000;j += i)
                sieve[j] = true;
    int n;
    while (1) {
        scanf("%d", &n);
        if (n == 0) break;
        for (int i = 3; i <= n / 2; i += 2) {
            if (!sieve[i] && !sieve[n - i]) {
                printf("%d = %d + %d\n", n, i, n - i);
                break;
            }
            if (i == n / 2) printf("Goldbach's conjecture is wrong.\n");
        }
    }
    return 0;
}