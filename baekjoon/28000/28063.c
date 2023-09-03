#include <stdio.h>

int main() {
    int n, x, y;
    scanf("%d%d%d", &n, &x, &y);
    int xside = x == 1 || x == n;
    int yside = y == 1 || y == n;
    int ans;
    if (n == 1) {
        ans = 0;
    } else if (xside && yside) {
        ans = 2;
    } else if (xside || yside) {
        ans = 3;
    } else {
        ans = 4;
    }
    printf("%d", ans);
}
