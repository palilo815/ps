#include <stdio.h>
#define scanf scanf_s

int gcd(int a, int b)
{
    if (a == 0) return b;
    return gcd(b % a, a);
}
int main()
{
    int N, a, b;
    scanf("%d %d %d", &N, &a, &b);
    a = gcd(a, b);
    if (N == 3) {
        scanf("%d", &b);
        a = gcd(a, b);
    }
    for (int i = 1;i <= a;++i)
        if (a % i == 0)
            printf("%d\n", i);
    return 0;
}