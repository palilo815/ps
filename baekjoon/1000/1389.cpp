#include <cstdio>
#include <cstring>
#define min(x,y) (x<y?x:y)
#define loop(i,n) for(int i=0;i<n;++i)

const int mxN = 100;
const int INF = 0x3f3f3f3f;

int d[mxN][mxN];

int main() {
    int N, M; scanf("%d%d", &N, &M);
    memset(d, 0x3f, sizeof(d));
    for (int i = 0, u, v; i < M; ++i) {
        scanf("%d%d", &u, &v); --u, --v;
        d[u][v] = d[v][u] = 1;
    }

    loop(k, N) loop(i, N) if (d[i][k] ^ INF)
        loop(j, N) if (d[k][j] ^ INF)
            d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

    int ans, _min = INF;
    loop(i, N) {
        int cnt = 0;
        loop(j, N) cnt += d[i][j];
        if (cnt < _min) _min = cnt, ans = i;
    }
    printf("%d", ans + 1);
    return 0;
}