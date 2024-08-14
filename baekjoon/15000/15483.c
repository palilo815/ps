#include <stdio.h>
#include <string.h>

char a[1001], b[1001];
int dp[1001];

int min_3(int x, int y, int z) {
    if (x < y) {
        return x < z ? x : z;
    } else {
        return y < z ? y : z;
    }
}

int main() {
    scanf("%s\n%s", a, b);
    const int n = strlen(a);
    const int m = strlen(b);
    for (int i = 0; i <= m; ++i) {
        dp[i] = i;
    }
    for (int i = 0; i < n; ++i) {
        int prv = dp[0];
        dp[0] = i + 1;
        for (int j = 0; j < m; ++j) {
            const int cur = dp[j + 1];
            dp[j + 1] = a[i] == b[j] ? prv : (min_3(prv, dp[j], dp[j + 1]) + 1);
            prv = cur;
        }
    }
    printf("%d", dp[m]);
}
