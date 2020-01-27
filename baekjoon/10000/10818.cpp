#include <stdio.h>

int main()
{
    int MAX = -1000000, MIN = 1000000;
    int n, x;
    scanf("%d", &n);
    while (n--) {
        scanf("%d", &x);
        if (x > MAX) MAX = x;
        if (x < MIN) MIN = x;
    }
    printf("%d %d", MIN, MAX);
    return 0;
}