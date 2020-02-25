#include <stdio.h>
#define scanf scanf_s

int cow[10][10];
void toggle(int r, int c) {
    for (int i = 0; i <= r; ++i) for (int j = 0; j <= c; ++j)
        cow[i][j] = !cow[i][j];
}
int main() {
    int N; scanf("%d", &N);
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j)
        scanf("%1d", &cow[i][j]);
    int ans = 0;
    for (int i = N - 1; i >= 0; --i) for (int j = N - 1; j >= 0; --j)
        if (cow[i][j]) {
            toggle(i, j);
            ++ans;
        }
    printf("%d", ans);
    return 0;
}