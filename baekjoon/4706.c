#include <stdio.h>
#include <math.h>

int main()
{
    double A, B;
    while (1) {
        scanf("%lf %lf", &A, &B);
        if (A == 0) break;
        double v = sqrt(1 - B * B / A / A);
        printf("%.3lf\n", v);
    }
    return 0;
}