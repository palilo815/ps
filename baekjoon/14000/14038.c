#include <stdio.h>

int main() {
    int ans[] = {-1, 3, 3, 2, 2, 1, 1};
    int win = 0;
    for (int i = 6; i--; getchar()) {
        win += getchar() == 'W';
    }
    printf("%d", ans[win]);
}
