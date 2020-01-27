#include <stdio.h>

int fac(int n)
{
    int ret = 1;
    for (int i = 2; i <= n; ++i)
        ret *= i;
    return ret;
}
int ACM(int n)
{
    int ret = 0, D = 1;
    while (n) {
        ret += (n % 10) * fac(D++);
        n /= 10;
    }
    return ret;
}
int main()
{
    int n;
    while (1) {
        scanf("%d", &n);
        if (n == 0) break;
        printf("%d\n", ACM(n));
    }
    return 0;
}