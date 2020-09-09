#include <cstdio>

const int mx = 104730;

bool sieve[mx];

int main() {
    sieve[0] = sieve[1] = true;
    for (int i = 2; i * i < mx; ++i)
        if (!sieve[i])
            for (int j = i * i; j < mx; j += i)
                sieve[j] = true;

    int N; scanf("%d", &N);
    for (int i = 0; i < mx; ++i)
        if (!sieve[i] && --N == 0) {
            printf("%d", i);
            break;
        }
    return 0;
}