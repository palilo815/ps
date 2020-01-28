#include <stdio.h>

int main()
{
    int n, ans = 0;
    scanf("%d", &n);
    while (n > 9) {
        int tmp = 1;
        while (n) {
            tmp *= (n % 10);
            n /= 10;
        }
        n = tmp;
        ++ans;
    }
    printf("%d", ans);
    return 0;
}