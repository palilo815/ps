#include <cstdio>
using ll = long long;

struct p {
    int x, y;
};

const int M = 10000;

int N, sx, sy;
p poly[M - 1];

ll ccw(int a, int b) {
    return 1LL * (poly[a].x - sx) * (poly[b].y - sy) -
           1LL * (poly[a].y - sy) * (poly[b].x - sx);
}
int main() {
    scanf("%d %d %d", &N, &sx, &sy);
    for (int i = 0; i < N - 1; ++i)
        scanf("%d %d", &poly[i].x, &poly[i].y);

    ll ans = 0;
    for (int i = 0; i < N - 2; ++i)
        ans += ccw(i, i + 1);
    if (ans < 0) ans = -ans;
    printf("%lld.%d", ans / 2, ans & 1 ? 5 : 0);
    return 0;
}