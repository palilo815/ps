#include <cstdio>
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)
using ll = long long;

int main() {
    int x1, y1, x2, y2; scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    int x3, y3, x4, y4; scanf("%d %d %d %d", &x3, &y3, &x4, &y4);

    ll X1 = max(x1, x3), Y1 = min(y1, y3);
    ll X2 = min(x2, x4), Y2 = max(y2, y4);

    if (X1 >= X2 || Y1 <= Y2) putchar('0');
    else printf("%lld", (X2 - X1) * (Y1 - Y2));
    return 0;
}