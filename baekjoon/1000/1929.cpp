#include <stdio.h>

bool sieve[1000001];
int main() {
    int a, b; scanf("%d %d", &a, &b);
    sieve[0] = sieve[1] = true;
    for (int i = 2; i * i <= b; ++i)
        if (!sieve[i])
            for (int j = i * i; j <= b; j += i)
                sieve[j] = true;
    for (int i = a; i <= b; ++i) if (!sieve[i])
        printf("%d\n", i);
    return 0;
}