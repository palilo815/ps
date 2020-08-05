#include <cstdio>

int main() {
    int T; scanf("%d", &T);
    for (int x, y; T--;) {
        scanf("%d%d", &x, &y);
        int dist = y - x, mov = 1, ans = 0;
        while (dist >= mov * 2) {
            ans += 2;
            dist -= mov++ * 2;
        }
        if (dist) ++ ans;
        if (dist > mov) ++ans;
        printf("%d\n", ans);
    }
    return 0;
}