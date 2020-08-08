#include <cstdio>

int main() {
    int money, N; scanf("%d%d", &money, &N);
    int coin = 0, cur = 1e9;
    for (int nxt; N--;) {
        scanf("%d", &nxt);
        money += cur * coin;
        coin = 0;
        if (cur < nxt) {coin += money / cur; money %= cur;}
        cur = nxt;
    }
    printf("%d", money + cur * coin);
    return 0;
}