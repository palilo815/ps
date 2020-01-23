#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int DP[100001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;

    // basis : 모든 숫자는 1의 합으로 나타낼 수 있다.
    for (int i = 1; i <= n; ++i) DP[i] = i;

    for (int i = 2; i * i <= n; ++i) {
        int POW = i * i;
        DP[POW] = 1;
        for (int j = POW + 1; j <= n; ++j)
            DP[j] = min(DP[j], DP[j - POW] + 1);
    }
    cout << DP[n];
    return 0;
}