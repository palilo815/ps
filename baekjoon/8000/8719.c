#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);
    for (int x, w, ans; t--;) {
        scanf("%d%d", &x, &w);
        for (ans = 0; x < w; ++ans, x <<= 1) {
            ;
        }
        printf("%d\n", ans);
    }
}
