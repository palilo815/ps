#include <stdio.h>

int main()
{
    int t, n;
    scanf("%d", &t);
    for (int i = 1; i <= t; ++i) {
        double X[2] = { 1001,-1001 }, Y[2] = { 1001,-1001 };
        scanf("%d", &n);
        while (n--) {
            double x, y;
            scanf("%lf %lf", &x, &y);
            if (x < X[0]) X[0] = x;
            if (x > X[1]) X[1] = x;
            if (y < Y[0]) Y[0] = y;
            if (y > Y[1]) Y[1] = y;
        }
        double Area = (X[1] - X[0]) * (Y[1] - Y[0]), Peri = 2 * (X[1] - X[0] + Y[1] - Y[0]);
        printf("Case %d: Area %.9lf, Perimeter %.9lf\n", i, Area, Peri);
    }
    return 0;
}