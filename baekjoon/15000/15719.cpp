#include <cstdio>

int main() {
    int N; scanf("%d", &N);
    int ans;
    switch ((N - 1) & 3) {
    case 0: ans = N - 1; break;
    case 1: ans = 1; break;
    case 2: ans = N; break;
    case 3: ans = 0;
    }

    while (N--) {
        int x; scanf("%d", &x);
        ans ^= x;
    }
    printf("%d", ans);
    return 0;
}