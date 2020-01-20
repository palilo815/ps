#include <stdio.h>
#define PI 3.14159265358979323846

int main()
{
    int T;
    double h, angle;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        scanf("%lf %lf", &h, &angle);
        double Tan = tan(angle * PI / 180.0);
        printf("Case %d: %.8lf\n", t, abs((1.0 - Tan) * h / Tan));
    }
    return 0;
}