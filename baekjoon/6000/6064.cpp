#include <stdio.h>

int gcd(int a, int b)
{
    if (a == 0) return b;
    return gcd(b % a, a);
}
int main()
{
    int T, M, N, x, y;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d %d", &M, &N, &x, &y);
        int ans = -1, g = gcd(M, N);
        int i = 0, j = 0, imax = N / g, jmax = M / g;

        // x_year과 y_year이 같은 경우를 찾는다.
        // i, j : 각각 몇 바퀴 돌았는지
        while (i < imax && j < jmax) {
            int x_year = M * i + x, y_year = N * j + y;
            if (x_year == y_year) {
                ans = x_year;
                break;
            }

            if (x_year < y_year) ++i;
            else ++j;
        }
        printf("%d\n", ans);
    }
    return 0;
}