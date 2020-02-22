#include <stdio.h>

int main() {
    int sum = 0, ans = 0;
    int N; scanf("%d", &N);
    while (N--) {
        int x; scanf("%d", &x);
        sum += x;
        if (ans < sum || ans == 0) ans = sum;
        if (sum < 0) sum = 0;
    }
    printf("%d", ans);
    return 0;
}