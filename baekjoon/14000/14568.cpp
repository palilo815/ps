#include <cstdio>

int main() {
    int N; scanf("%d", &N);
    int ans = 0;
    for (int i = 2; i + 2 < N; i += 2)
        ans += (N - i - 2) / 2;
    printf("%d", ans);
    return 0;
}