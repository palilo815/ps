#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int MAX = 16;
int N, cost[MAX][MAX], cache[MAX][1 << MAX];

int TSP(int u, int visited)
{
    if (visited == (1 << N) - 1)
        return (cost[u][0] ? cost[u][0] : INT_MAX / 2);

    int& ret = cache[u][visited];
    if (ret) return ret;

    ret = INT_MAX / 2;
    loop(v, N) if (cost[u][v] && !(visited & (1 << v)))
        ret = min(ret, cost[u][v] + TSP(v, visited + (1 << v)));
    return ret;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> N;
    loop(i, N) loop(j, N) cin >> cost[i][j];
    cout << TSP(0, 1);
    return 0;
}