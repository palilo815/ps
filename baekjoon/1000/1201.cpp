#include <cstdio>

int main() {
    int N, M, K; scanf("%d %d %d", &N, &M, &K);
    if (N < M + K - 1 || N > M * K) {
        printf("-1");
        return 0;
    }
    for (int i = K; i >= 1; --i)
        printf("%d ", i);
    for (int i = K; i < N; ) {
        int j = i + (N - i) / --M;
        for (int k = j; k > i; --k)
            printf("%d ", k);
        i = j;
    }
    return 0;
}