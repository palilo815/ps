#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long
#define MOD 1000000000

ll DP[1000001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    DP[1] = 0;
    DP[2] = 1;
    for (int i = 3;i <= n;++i) {
        DP[i] = (i - 1) * ((DP[i - 1] + DP[i - 2]) % MOD);
        DP[i] %= MOD;
    }
    cout << DP[n];
    return 0;
}