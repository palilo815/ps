#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)

const int max_N = 100;
bool adj[max_N][max_N];
int main()
{
    int N; scanf("%d", &N);
    loop(i, N) loop(j, N) scanf("%d", &adj[i][j]);
    loop(k, N) loop(i, N) loop(j, N) adj[i][j] = adj[i][j] || (adj[i][k] && adj[k][j]);
    loop(i, N) {
        loop(j, N) printf("%d ", adj[i][j]);
        putchar('\n');
    }
    return 0;
}