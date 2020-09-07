#include <cstdio>

int main() {
    int N, K, P, W;
    scanf("%d%d%d%d", &N, &K, &P, &W);
    printf("%d", (P + W - 1) / W);
    return 0;
}