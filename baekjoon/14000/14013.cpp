#include <stdio.h>

int main()
{
    double A, B;
    scanf("%lf %lf", &A, &B);
    double to_A = A / B, to_B = B / A;
    int T;
    scanf("%d", &T);
    while (T--) {
        double x;
        char c;
        scanf("%lf %c", &x, &c);
        if (c == 'A') x *= to_B;
        else x *= to_A;
        printf("%.8lf\n", x);
    }
    return 0;
}