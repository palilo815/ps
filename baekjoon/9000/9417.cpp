#include <stdio.h>

int main()
{
    int T, t, m;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &t, &m);
        int a = 1, b = 1, ans = 0;
        do {
            int tmp = a;
            a = b;
            b = (tmp + b) % m;
            ++ans;
        } while (a != 1 || b != 1);
        printf("%d %d\n", t, ans);
    }
    return 0;
}