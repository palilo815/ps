#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define MOD 1000000000

int DP[201][201];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, k; cin >> n >> k;
    loop(i, n + 1)
        DP[1][i] = 1;
    for (int i = 2; i <= k; ++i)
        loop(ADD, n + 1)
            for (int RES = ADD; RES <= n; ++RES) {
                DP[i][RES] += DP[i - 1][RES - ADD];
                DP[i][RES] %= MOD;
            }
    cout << DP[k][n];
    return 0;
}