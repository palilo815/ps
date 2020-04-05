#include <cstdio>

const int max_N = 1000000;

bool sieve[max_N];

int main() {
    sieve[0] = sieve[1] = true;
    for (int i = 2; i * i <= max_N; ++i)
        if (!sieve[i])
            for (int j = i * i; j <= max_N; j += i)
                sieve[j] = true;

    int T; scanf("%d", &T);
    while (T--) {
        int N; scanf("%d", &N);
        int ans = (N == 4 ? 1 : 0);
        for (int i = 3; i <= N / 2; i += 2)
            if (!sieve[i] && !sieve[N - i])
                ++ans;
        printf("%d\n", ans);
    }
    return 0;
}