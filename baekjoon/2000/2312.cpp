#include <cstdio>

const int mxN = 1e5;

bool sieve[mxN + 1];

void solve() {
    int N; scanf("%d", &N);
    for (int i = 2; N ^ 1; ++i)
        if (!sieve[i] && N % i == 0) {
            int cnt = 1; N /= i;
            while (N % i == 0)
                ++cnt, N /= i;
            printf("%d %d\n", i, cnt);
        }
}
int main() {
    sieve[0] = sieve[1] = true;
    for (int i = 2; i * i <= mxN; ++i)
        if (!sieve[i])
            for (int j = i * 2; j <= mxN; j += i)
                sieve[j] = true;

    int T; scanf("%d", &T);
    while (T--) solve();
    return 0;
}