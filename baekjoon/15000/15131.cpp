#include <cstdio>
/*
    이 셋만 사용하면 된다.
    1 -> 2
    4 -> 4
    7 -> 3
*/
int main() {
    int N; scanf("%d", &N);

    int ans = 7 * (N / 3); N %= 3;
    if (N == 1) ans -= 3;
    if (N == 2) ++ans;
    printf("%d", ans);
    return 0;
}