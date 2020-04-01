#include <stdio.h>

int main() {
    int N; scanf("%d", &N);
    if (N == 3) { printf("-1"); return 0; }

    if (N % 2) {
        for (int i = 1; i <= N / 2; ++i) printf("%d\n", i + 1);
        printf("%d\n%d", 1, N);
        for (int i = N / 2 + 3; i <= N; ++i) printf("\n%d", i - 1);
    }
    else {
        for (int i = 1; i < N / 2; ++i) printf("%d\n", i + 1);
        printf("%d\n%d", 1, N);
        for (int i = N / 2 + 2; i <= N; ++i) printf("\n%d", i - 1);
    }
    return 0;
}