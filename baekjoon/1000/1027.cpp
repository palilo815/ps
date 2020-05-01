#include <cstdio>
typedef long long ll;

const int max_N = 50;

ll h[max_N];

int ccw(int x1, int x2, int x3) {
    ll ret = (x1 * h[x2] + x2 * h[x3] + x3 * h[x1]) - (h[x1] * x2 + h[x2] * x3 + h[x3] * x1);
    if (ret > 0) return 1;
    else if (ret < 0) return -1;
    return 0;
}
int seen(int l, int r) {
    for (int i = l + 1; i < r; ++i)
        if (ccw(l, i, r) != 1)
            return 0;
    return 1;
}
int main() {
    int N; scanf("%d", &N);
    for (int i = 0; i < N; ++i)
        scanf("%lld", &h[i]);

    int ans = 0;
    for (int i = 0; i < N; ++i) {
        int cnt = 0;
        for (int l = 0; l < i; ++l)
            cnt += seen(l, i);
        for (int r = i + 1; r < N; ++r)
            cnt += seen(i, r);
        if (cnt > ans) ans = cnt;
    }
    printf("%d", ans);
    return 0;
}