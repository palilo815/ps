#include <cstdio>
#define swap(a,b) do{auto tmp=a;a=b;b=tmp;}while(0)
using ll = long long;

struct p {
    ll x, y;
    bool operator >(const p& rhs) const {
        return x == rhs.x ? y > rhs.y : x > rhs.x;
    }
    bool operator <=(const p& rhs) const {
        return x == rhs.x ? y <= rhs.y : x < rhs.x;
    }
};
int ccw(p& a, p& b, p& c) {
    ll ret = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    return ret ? (ret > 0 ? 1 : -1) : 0;
}
int main() {
    p a[4];
    for (int i = 0; i < 4; ++i)
        scanf("%lld %lld", &a[i].x, &a[i].y);

    int A = ccw(a[0], a[1], a[2]) * ccw(a[0], a[1], a[3]);
    int B = ccw(a[2], a[3], a[0]) * ccw(a[2], a[3], a[1]);
    int ans;
    if (A | B) ans = A <= 0 && B <= 0;
    else {
        if (a[0] > a[1]) swap(a[0], a[1]);
        if (a[2] > a[3]) swap(a[2], a[3]);
        ans = a[0] <= a[3] && a[2] <= a[1];
    }
    printf("%d", ans);
    return 0;
}