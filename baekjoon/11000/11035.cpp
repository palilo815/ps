#include <cstdio>
#include <cstring>

const int mxN = 1001;

bool sieve[mxN];

int main() {
    for (int N, K; ~scanf("%d%d", &N, &K);) {
        memset(sieve + 1, 0, N);
        for (int i = 2;; ++i)
            if (!sieve[i])
                for (int j = i; j <= N; j += i)
                    if (!sieve[j]) {
                        if (--K == 0) {
                            printf("%d\n", j);
                            goto out;
                        }
                        sieve[j] = true;
                    }
out :;
    }
    return 0;
}