#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int DP[1001][1001];
int main()
{
    int n, k; cin >> n >> k;
    
    // basis
    loop(i, n + 1) DP[i][0] = 1;

    // 점화식
    // DP[i][j] = DP[i - 1][j - 1] + DP[i - 1][j]
    for (int i = 1;i <= n;++i)
        for (int j = 1;j <= k;++j)
            DP[i][j] = (DP[i - 1][j - 1] + DP[i - 1][j]) % 10007;
    cout << DP[n][k];
    return 0;
}