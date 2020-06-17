#include <cstdio>

int main() {
    int N, A, B, C, D; scanf("%d %d %d %d %d", &N, &A, &B, &C, &D);
    int x = ((N - 1) / A + 1) * B;
    int y = ((N - 1) / C + 1) * D;
    printf("%d", x < y ? x : y);
    return 0;
}