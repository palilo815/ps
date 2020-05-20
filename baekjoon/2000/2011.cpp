#include <stdio.h>

int main() {
    char prv = getchar(), cur;
    int a = 1, b = prv != '0';
    int ans = b;

    while ((cur = getchar()) != EOF && cur != '\n') {
        ans = 0;
        if (cur != '0') ans += b;
        if (prv == '1' || (prv == '2' && cur < '7')) ans += a;
        ans %= 1000000;

        a = b;
        b = ans;
        prv = cur;
    }
    printf("%d", ans);
}