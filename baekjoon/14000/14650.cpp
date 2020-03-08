#include <stdio.h>

int ans, N;
void solve(int n, int sum) {
    if (n == N) {
        if (sum % 3 == 0) ++ans;
        return;
    }
    solve(n + 1, sum);
    solve(n + 1, sum + 1);
    solve(n + 1, sum + 2);
}
int main() {
    scanf("%d", &N);
    solve(1, 1);
    solve(1, 2);
    printf("%d", ans);
    return 0;
}