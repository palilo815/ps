#include <stdio.h>

inline int min(int a, int b) {
    return (a < b ? a : b);
}
inline int min(int a, int b, int c) {
    b = min(b, c);
    return (a < b ? a : b);
}
int main() {
    int N; scanf("%d", &N);
    int a3 = 0, a5 = 0;
    int b3 = 0, b5 = 0;
    int x, ans = 0;
    while (N--) {
        scanf("%d", &x);
        int buy_5 = min(b3, x);
        b3 -= buy_5, b5 += buy_5, ans += 2 * buy_5, x -= buy_5;

        int buy_7 = min(a5, b5, x);
        b5 -= buy_7, ans += 2 * buy_7, x -= buy_7;

        ans += 3 * x;
        a3 = b3, a5 = b5;
        b3 = x, b5 = buy_5;
    }
    printf("%d", ans);
    return 0;
}