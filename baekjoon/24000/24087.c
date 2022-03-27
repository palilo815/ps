#include <stdio.h>

int main() {
    int s, a, b;
    scanf("%d%d%d", &s, &a, &b);
    int ans = 250;
    while (a < s) a += b, ans += 100;
    printf("%d", ans);
}
