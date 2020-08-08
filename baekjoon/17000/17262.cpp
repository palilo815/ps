#include <cstdio>

int main() {
    int N; scanf("%d", &N);
    int max_s = 0, min_e = 1e9;
    for (int s, e; N--;) {
        scanf("%d%d", &s, &e);
        if (s > max_s) max_s = s;
        if (e < min_e) min_e = e;
    }
    printf("%d", max_s - min_e < 0 ? 0 : max_s - min_e);
}