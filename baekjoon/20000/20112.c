#include <stdio.h>

#define MAX_N 100

char grid[MAX_N][MAX_N + 1];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", grid[i]);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] != grid[j][i]) {
                puts("NO");
                return 0;
            }
        }
    }
    puts("YES");
}
