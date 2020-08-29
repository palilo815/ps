#include <cstdio>

int main() {
    for (int k;;) {
        scanf("%d", &k);
        if (!k) break;

        int l = 1, r = 50, m, ans = 0;
        if (k & 1) ++k, ++ans;
        k >>= 1;
        do {
            ++ans;
            m = l + (r - l) / 2;
            k < m ? (r = m - 1) : (l = m + 1);
        } while (m ^ k);
        printf("%d\n", ans);
    }
    return 0;
}