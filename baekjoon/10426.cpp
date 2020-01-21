#include <stdio.h>

int main()
{
    int DAY[13] = { 29,31,28,31,30,31,30,31,31,30,31,30,31 };
    int n, y, m, d;
    scanf("%d", &y); getchar();
    scanf("%d", &m); getchar();
    scanf("%d %d", &d, &n);
    n += d - 1;
    while (1) {
        int day;
        if (m == 2 && ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)) day = DAY[0];
        else day = DAY[m];
        if (n <= day) break;
        n -= day;
        ++m;
        if (m > 12) { m = 1; ++y; }
    }
    printf("%d-%02d-%02d", y, m, n);
    return 0;
}