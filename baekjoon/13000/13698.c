#include <stdio.h>

int main() {
    char s[201];
    scanf("%s", s);
    const int rule[6][2] = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}};
    int cup[4] = {1, 0, 0, 2};
    for (char* i = s; *i; ++i) {
        const int u = rule[*i - 'A'][0];
        const int v = rule[*i - 'A'][1];
        const int tmp = cup[u];
        cup[u] = cup[v];
        cup[v] = tmp;
    }
    for (int i = 0; i != 4; ++i) {
        if (cup[i] == 1) {
            printf("%d\n", i + 1);
        }
    }
    for (int i = 0; i != 4; ++i) {
        if (cup[i] == 2) {
            printf("%d\n", i + 1);
        }
    }
}
