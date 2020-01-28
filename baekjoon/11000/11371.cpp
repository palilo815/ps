#include <stdio.h>
#include <math.h>
#define PI 3.14159265358979323846

int main()
{
    double x, y;
    while (1) {
        scanf("%lf %lf", &x, &y);
        if (x == 0 && y == 0) break;
        double angle = atan(y / x) * 180.0 / PI;
        printf("%d\n", (int)(angle + 0.5));
    }
    return 0;
}