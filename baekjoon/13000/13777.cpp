#include <cstdio>

int main() {
    for (int k;;) {
        scanf("%d", &k);
        if (!k) break;

        int l = 1, r = 50, m;
        do {
            m = l + (r - l) / 2;
            printf("%d ", m);
            k < m ? (r = m - 1) : (l = m + 1);
        } while (m ^ k);
        putchar('\n');
    }
    return 0;
}