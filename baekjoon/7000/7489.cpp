#include <stdio.h>
#define scanf scanf_s

int cnt(int N, int div) {
    int ret = 0;
    while (N) {
        ret += N / div;
        N /= div;
    }
    return ret;
}
int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int N; scanf("%d", &N);
        int a = cnt(N, 2), b = cnt(N, 5);
        if (a < b) b = a;
        else a = b;

        int ans = 1;
        for (int i = 1; i <= N; ++i) {
            int j = i;
            while (a && j % 2 == 0) j /= 2, --a;
            while (b && j % 5 == 0) j /= 5, --b;
            ans *= j;
            ans %= 10;
        }
        printf("%d\n", ans);
    }
    return 0;
}