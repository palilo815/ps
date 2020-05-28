#include <cstdio>
#define loop(i,n) for(int i=0;i<n;++i)
#define swap(a,b) do{int tmp=a;a=b;b=tmp;}while(0)

const int max_N = 1001;

int x1[max_N], x2[max_N], y1[max_N], y2[max_N];
int parent[max_N];

int _find(int u) {
    if (parent[u] == u) return u;
    return parent[u] = _find(parent[u]);
}
void _merge(int u, int v) {
    u = _find(u), v = _find(v);
    parent[u] = v;
}
int overlap(int a, int b) {
    if (x2[b] < x1[a] || x2[a] < x1[b]) return 0;
    if (y2[b] < y1[a] || y2[a] < y1[b]) return 0;

    if (x1[b] < x1[a] && x2[a] < x2[b] && y1[b] < y1[a] && y2[a] < y2[b]) return 0;
    if (x1[a] < x1[b] && x2[b] < x2[a] && y1[a] < y1[b] && y2[b] < y2[a]) return 0;
    return 1;
}
int main() {
    int N; scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        scanf("%d %d %d %d", &x1[i], &y1[i], &x2[i], &y2[i]);
        if (x1[i] > x2[i]) swap(x1[i], x2[i]);
        if (y1[i] > y2[i]) swap(y1[i], y2[i]);
    }
    
    ++N;
    loop(i, N) parent[i] = i;
    loop(i, N - 1) for (int j = i + 1; j < N; ++j)
        if (overlap(i, j)) _merge(i, j);

    int ans = 0;
    loop(i, N) if (i == _find(i)) ++ans;
    printf("%d", ans - 1);
    return 0;
}