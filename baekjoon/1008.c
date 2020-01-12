#include <stdio.h>

int main() {
    int A, B;
    scanf("%d %d", &A, &B);
    double d = (double)A / B;
    printf("%.15lf", d);
    return 0;
}