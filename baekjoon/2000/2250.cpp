#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
const int max_N = 10000;

bool check[max_N + 1];
int child[max_N + 1][2];
int in[max_N + 2], out[max_N + 2];

int cnt;

void DFS(int u, int level) {
    if (child[u][0] != -1) DFS(child[u][0], level + 1);

    ++cnt;
    if (!in[level]) in[level] = cnt;
    out[level] = cnt;

    if (child[u][1] != -1) DFS(child[u][1], level + 1);
}
int main() {
    int N; scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        int u, l, r; scanf("%d %d %d", &u, &l, &r);
        child[u][0] = l, child[u][1] = r;
        check[l] = check[r] = true;
    }

    for (int i = 1; i <= N; ++i) if (!check[i]) {
        DFS(i, 1);
        break;
    }

    int w = -1, level = -1;
    for (int i = 1; in[i]; ++i)
        if (out[i] - in[i] > w) {
            level = i;
            w = out[i] - in[i];
        }
    printf("%d %d", level, w + 1);
    return 0;
}