#include <stdio.h>

int main() {
    int N, sum = 0, M = 0;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        int score; scanf("%d", &score);
        sum += score;
        if (score > M) M = score;
    }
    printf("%.8lf", 1.0 * sum / N / M * 100);
    return 0;
}