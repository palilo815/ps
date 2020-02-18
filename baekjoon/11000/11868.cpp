#include <stdio.h>

int main()
{
    int N; scanf("%d", &N);
    int x = 0, tmp;
    while (N--) {
        scanf("%d", &tmp);
        x ^= tmp;
    }
    printf("%s", x ? "koosaga" : "cubelover");
    return 0;
}