#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);
    for (int a, b, c; t--;) {
        scanf("%d%d%d", &a, &b, &c);
        int ans = 0;
        for (int x = 1; x <= a; ++x) {
            for (int y = 1; y <= b; ++y) {
                int key = x % y;
                for (int z = 1; z <= c; ++z) {
                    ans += key == y % z && key == z % x;
                }
            }
        }
        printf("%d\n", ans);
    }
}
