#include <cstdio>
#define loop(i,n) for(int i=0;i<n;++i)
#define swap(a,b) do{auto tmp=a;a=b;b=tmp;}while(0)
using ll = long long;

struct p {
    int x, y;
    bool operator >(const p& rhs) const {
        return x == rhs.x ? y > rhs.y : x > rhs.x;
    }
    bool operator <=(const p& rhs) const {
        return x == rhs.x ? y <= rhs.y : x < rhs.x;
    }
    bool operator ==(const p& rhs) const {
        return x == rhs.x && y == rhs.y;
    }
};

const int max_N = 10000;

p poly[max_N + 4];

int ccw(int a, int b, int c) {
    ll ret = 1ll * (poly[b].x - poly[a].x) * (poly[c].y - poly[a].y) -
             1ll * (poly[b].y - poly[a].y) * (poly[c].x - poly[a].x);
    return ret ? (ret > 0 ? 1 : -1) : 0;
}
int cross(int a, int b, int c, int d) {
    int A = ccw(a, b, c) * ccw(a, b, d);
    int B = ccw(c, d, a) * ccw(c, d, b);
    if (A | B) return A <= 0 && B <= 0;
    if (poly[a] > poly[b]) swap(a, b);
    if (poly[c] > poly[d]) swap(c, d);
    return poly[a] <= poly[d] && poly[c] <= poly[b];
}
int main() {
    int N; scanf("%d", &N);
    for (int i = 0; i < N + 3; ++i)
        scanf("%d %d", &poly[i].x, &poly[i].y);
    poly[N + 3].x = -1;

    loop(i, 3) {
        poly[N + 3].y = poly[N + i].y + 1;
        int cnt = 0;
        loop(j, N) {
            if (poly[j] == poly[N + i]) {cnt = 1; break;}
            cnt += cross(j, (j + 1) % N, N + i, N + 3);
        }
        printf("%d\n", cnt & 1);
    }
    return 0;
}