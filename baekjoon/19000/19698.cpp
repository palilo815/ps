#include <cstdio>

int main() {
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, W, H, L;
    scanf("%d%d%d%d", &N, &W, &H, &L);
    int N2 = (W / L) * (H / L);
    printf("%d", N < N2 ? N : N2);
    return 0;
}