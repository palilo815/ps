#include <stdio.h>

int main()
{
    int ans, n;
    char c;
    scanf("%d", &ans);
    while (1) {
        scanf("%c", &c);
        if (c == '=') break;
        scanf("%d", &n);
        if (c == '+') ans += n;
        else if (c == '-') ans -= n;
        else if (c == '*') ans *= n;
        else ans /= n;
    }
    printf("%d", ans);
    return 0;
}