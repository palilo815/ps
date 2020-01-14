#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int DP[100000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) cin >> DP[i];
    for (int i = 1; i < n; ++i)
        DP[i] = max(DP[i], DP[i - 1] + DP[i]);
    int ans = INT32_MIN;
    loop(i, n)
        ans = max(ans, DP[i]);
    cout << ans;
    return 0;
}