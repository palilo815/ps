#include <stdio.h>

int solve(int n)
{
    int f2 = 0, f0 = 0, f1 = 0, f8 = 0;
    while (n) {
        int x = n % 10;
        if (x == 2) ++f2;
        else if (x == 0) ++f0;
        else if (x == 1) ++f1;
        else if (x == 8) ++f8;
        else return 0;
        n /= 10;
    }
    if (f2 && f0 && f1 && f8) {
        if (f2 == f0 && f0 == f1 && f1 == f8) return 8;
        return 2;
    }
    return 1;
}
int main()
{
    int n;
    scanf("%d", &n);
    printf("%d", solve(n));
    return 0;
}