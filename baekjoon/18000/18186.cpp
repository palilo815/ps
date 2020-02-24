#include <stdio.h>
typedef long long ll;
#define scanf scanf_s
inline int min(int a, int b) {
    return (a < b ? a : b);
}
inline int min(int a, int b, int c) {
    b = min(b, c);
    return (a < b ? a : b);
}
int main() {
    int N;
    ll B, C; scanf("%d %lld %lld", &N, &B, &C);
    int a1 = 0, a2 = 0; // 이전 이전 케이스
    int b1 = 0, b2 = 0; // 이전 케이스

    int x;
    ll ans = 0;
    if (B <= C) {
        while (N--) {
            scanf("%d", &x);
            ans += x;
        }
        printf("%lld", ans * B);
        return 0;
    }

    while (N--) {
        scanf("%d", &x);
        int buy_2 = min(b1, x);
        b1 -= buy_2, b2 += buy_2, ans += C * buy_2; x -= buy_2;

        int buy_3 = min(a2, b2, x);
        b2 -= buy_3, ans += C * buy_3, x -= buy_3;

        ans += B * x;
        a1 = b1, a2 = b2;
        b1 = x, b2 = buy_2;
    }
    printf("%lld", ans);
    return 0;
}