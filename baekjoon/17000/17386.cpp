#include <cstdio>
typedef long long ll;

ll x[4], y[4];
int ccw(int i1, int i2, int i3) {
    ll ret = (x[i1] * y[i2] + x[i2] * y[i3] + x[i3] * y[i1]) -
             (y[i1] * x[i2] + y[i2] * x[i3] + y[i3] * x[i1]);
    if (ret > 0) return 1;
    else if (ret < 0) return -1;
    return 0;
}
int main() {
    for (int i = 0; i < 4; ++i)
        scanf("%lld %lld", &x[i], &y[i]);
    
    int cross = 1;
    if (ccw(0, 1, 2) == ccw(0, 1, 3)) cross = 0;
    if (ccw(2, 3, 0) == ccw(2, 3, 1)) cross = 0;
    printf("%d", cross);
    return 0;
}