#include <stdio.h>

int main() {
    int t1, t2, m1, m2;
    scanf("%d%d%d%d", &t1, &m1, &t2, &m2);
    int res = t2 * 60 + m2 - (t1 * 60 + m1);
    if (res < 0) res += 24 * 60;
    printf("%d %d", res, res / 30);
}
