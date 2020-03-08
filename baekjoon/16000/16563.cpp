#include <stdio.h>

const int max_num = 5000000;

bool sieve[max_num + 1];
int prime[348513];

int main() {
    for (int i = 2; i * i <= max_num; ++i) if (!sieve[i])
        for (int j = i * i; j <= max_num; j += i)
            sieve[j] = true;
    int pos = 0;
    for (int i = 2; i <= max_num; ++i) if (!sieve[i])
        prime[pos++] = i;

    int N; scanf("%d", &N);
    while (N--) {
        int num; scanf("%d", &num);
        int i = 0, p = 2;
        while (p * p <= num) {
            if (num % p == 0) {
                printf("%d ", p);
                num /= p;
            }
            else p = prime[++i];
        }
        if (num != 1) printf("%d", num);
        putchar('\n');
    }
    return 0;
}