#include <cstdio>

int main() {
    int k, w, m; scanf("%d %d %d", &k, &w, &m);
    printf("%d", k >= w ? 0 : (w - k - 1) / m + 1);
    return 0;
}