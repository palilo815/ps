#include <cstdio>
#include <cstring>
#define loop(i,n) for(int i=0;i<n;++i)
typedef long long ll;

const int max_N = 50;
const int mod = 1000000007;

int N;
ll adj[max_N][max_N];

void multiply(ll A[][max_N], ll B[][max_N])
{
    ll tmp[max_N][max_N];
    loop(i, N) loop(j, N) {
        ll x = 0;
        loop(k, N) x += (A[i][k] * B[k][j]) % mod;
        tmp[i][j] = x % mod;
    }
    memcpy(A, tmp, sizeof(tmp));
}
void power(int D) {
    if (D == 1) return;
    ll tmp[max_N][max_N];
    memcpy(tmp, adj, sizeof(tmp));
    power(D / 2);
    multiply(adj, adj);
    if (D & 1) multiply(adj, tmp);
}
int main() {
    int M; scanf("%d %d", &N, &M);
    while (M--) {
        int u, v; scanf("%d %d", &u, &v);
        --u, --v;
        adj[u][v] = adj[v][u] = 1;
    }

    int D; scanf("%d", &D);
    power(D);
    printf("%lld", adj[0][0]);
    return 0;
}