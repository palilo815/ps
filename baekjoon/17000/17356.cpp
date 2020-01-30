#include <stdio.h>
#include <math.h>

int main()
{
    double A, B, M;
    scanf("%lf %lf", &A, &B);
    M = (B - A) / 400;
    printf("%.20lf", 1 / (1 + pow(10.0, M)));
    return 0;
}