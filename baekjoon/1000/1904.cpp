#include<iostream>
using namespace std;
#define MOD 15746

int DP[1000001];
int main()
{
    int n; cin >> n;
    DP[0] = DP[1] = 1;
    for (int i = 2; i < n + 1; ++i)
        DP[i] = (DP[i - 1] + DP[i - 2]) % MOD;
    cout << DP[n];
    return 0;
}