#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 2000;
int n, cache[max_N][max_N], L[max_N], R[max_N];
int DP(int a, int b)
{
    if (a == n || b == n) return 0;
    int& ret = cache[a][b];
    if (ret != -1) return ret;

    ret = max(DP(a + 1, b), DP(a + 1, b + 1));
    if (L[a] > R[b])
        ret = max(ret, DP(a, b + 1) + R[b]);
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    memset(cache, -1, sizeof(cache));
    cin >> n;
    loop(i, n) cin >> L[i];
    loop(i, n) cin >> R[i];
    cout << DP(0, 0);
    return 0;
}