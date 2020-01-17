#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int n;
double arr[10000], cache[10000];
double DP(int start)
{
    if (start == n) return 1.0;
    double& ret = cache[start];
    if (ret != -1) return ret;
    ret = arr[start];
    return ret = max(ret, ret * DP(start + 1));
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    loop(i, 10000) cache[i] = -1;
    cin >> n;
    loop(i, n) cin >> arr[i];
    double ans = 0;
    loop(i, n)
        ans = max(ans, DP(i));
    printf("%.3lf", ans);
    return 0;
}