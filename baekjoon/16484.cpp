#include <stdio.h>
int main()
{
    double XY, PM, Ans;
    scanf("%lf %lf", &XY, &PM);
    printf("%.1lf", (XY - 2.0 * PM) / 2.0);
    return 0;
}