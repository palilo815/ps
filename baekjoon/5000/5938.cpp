#include <cstdio>
#include <cstring>

const int mxN = 251;

int par[mxN];

int _find(int u) {
    return ~par[u] ? (par[u] = _find(par[u])) : u;
}
int main() {
    int N, M; scanf("%d%d", &N, &M);
    memset(par + 1, -1, sizeof(int) * N);
    for (int u, v; M--;) {
        scanf("%d%d", &u, &v);
        u = _find(u), v = _find(v);
        if (u ^ v) par[u] = v;
    }

    int root = _find(1), flag = 0;
    for (int i = 2; i <= N; ++i)
        if (_find(i) ^ root) {
            printf("%d\n", i);
            flag = 1;
        }
    if (!flag) putchar('0');
    return 0;
}