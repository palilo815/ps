#include <stdio.h>

int main() {
    int row, col; scanf("%d %d", &row, &col);
    int ans;
    if (row == 1) ans = 1;
    else if (row == 2) {
        ans = (col + 1) / 2;
        if (ans > 4) ans = 4;
    }
    else if (col < 7) ans = (col > 4 ? 4 : col);
    else ans = col - 2;
    printf("%d", ans);
    return 0;
}