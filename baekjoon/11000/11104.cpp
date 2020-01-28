#include <stdio.h>
#define scanf scanf_s
int main()
{
    int T; scanf("%d", &T); getchar();
    while (T--) {
        char c;
        int n = 0;
        for (int i = 23; i >= 0; --i) {
            scanf("%c", &c);
            if (c == '1') n += 1 << i;
        }
        getchar();
        printf("%d\n", n);
    }
    return 0;
}