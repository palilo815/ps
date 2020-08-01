#include <cstdio>

int main() {
    int N; scanf("%d", &N);
    int ans = 0;
    for (int x; N--; ans += x != 0) {
        scanf("%d", &x);
        if (x == 1) x = 0;
        for (int i = 2; i * i <= x; ++i)
            if (x % i == 0) x = 0;
    }
    printf("%d", ans);
    return 0;
}