#include <stdio.h>
typedef long long ll;

const int MAX = 1000000;

bool sieve[MAX + 1];
bool is_prime(ll num) {
    for (int i = 2; i <= MAX; ++i) if (!sieve[i])
        if (num % i == 0) return false;
    return true;
}
int main() {
    for (int i = 2; i * i <= MAX; ++i) if (!sieve[i])
        for (int j = i * i; j <= MAX; j += i)
            sieve[j] = true;

    int N; scanf("%d", &N);
    while (N--) {
        ll num; scanf("%lld", &num);
        printf("%s\n", (is_prime(num) ? "YES" : "NO"));
    }
    return 0;
}