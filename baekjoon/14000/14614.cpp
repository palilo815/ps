#include <cstdio>
int main() {
    int A, B;
    char C[101];
    scanf("%d %d %s", &A, &B, C);

    int i = 0;
    while (C[i + 1]) ++i;
    if ((C[i] - '0') & 1) A ^= B;

    printf("%d", A);
    return 0;
}