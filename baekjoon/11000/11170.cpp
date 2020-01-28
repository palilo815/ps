#include <stdio.h>
#define scanf scanf_s
int count0(int n)
{
    if (n == 0) return 1;
    int ret = 0, d;
    while (n) {
        d = n % 10;
        if (d == 0) ++ret;
        n /= 10;
    }
    return ret;
}
int main()
{
    int T, a, b;
    scanf("%d", &T);
    while (T--) {
        int ans = 0;
        scanf("%d %d", &a, &b);
        for (int i = a; i <= b; ++i)
            ans += count0(i);
        printf("%d\n", ans);
    }
    return 0;
}