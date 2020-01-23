#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define M 16

int n, dist[M][M], Cache[M][1 << M];
int TSP(int here, int visited)
{
    if (visited == (1 << n) - 1) {
        if (dist[here][0])
            return dist[here][0];
        return INT32_MAX / 2;
    }
    int& ret = Cache[here][visited];
    if (ret) return ret;
    ret = INT32_MAX / 2;
    loop(next, n) {
        if (dist[here][next] == 0) continue;
        if (visited & (1 << next)) continue;
        int cand = dist[here][next] + TSP(next, visited + (1 << next));
        ret = min(ret, cand);
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> n;
    loop(i, n) loop(j, n) cin >> dist[i][j];
    cout << TSP(0, 1);
    return 0;
}