#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int n, Cache[1001], Score[1000];
int DP(int start)
{
    int& ret = Cache[start];
    if (ret != -1) return ret;

    ret = 0;
    int MAX = Score[start], MIN = Score[start];
    for (int LastMem = start; LastMem < n; ++LastMem) {
        MAX = max(MAX, Score[LastMem]), MIN = min(MIN, Score[LastMem]);
        ret = max(ret, MAX - MIN + DP(LastMem + 1));
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    memset(Cache, -1, sizeof(Cache));
    cin >> n;
    Cache[n - 1] = Cache[n] = 0;
    loop(i, n) cin >> Score[i];
    cout << DP(0);
    return 0;
}