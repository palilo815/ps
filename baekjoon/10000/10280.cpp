#include <cstdio>

int main() {
    int N, K; scanf("%d%d", &N, &K);
    int my_turn, pizza;
    if (K - 1 < N - K) my_turn = K - 1, pizza = N - 2 * K;
    else my_turn = N - K, pizza = N - 2 * (N - K) - 1;
    printf("%s", my_turn < pizza ? "NO" : "YES");
    return 0;
}