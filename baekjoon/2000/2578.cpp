#include <stdio.h>

int row[5], col[5], dia[2];
int main() {
    int pos[26];
    for (int i = 0; i < 25; ++i) {
        int num; scanf("%d", &num);
        pos[num] = i;
    }

    int bingo = 0;
    for (int i = 1; i <= 25; ++i) {
        int num; scanf("%d", &num);
        int r = pos[num] / 5, c = pos[num] % 5;

        if (++row[r] == 5) ++bingo;
        if (++col[c] == 5) ++bingo;
        if (r == c && ++dia[0] == 5) ++bingo;
        if (r + c == 4 && ++dia[1] == 5) ++bingo;

        if (bingo >= 3) {
            printf("%d", i);
            return 0;
        }
    }
    return 0;
}