#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int coin[100], DP[10001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, k; cin >> n >> k;
    loop(i, n) cin >> coin[i];

    DP[0] = 1;	// basis : 0원 만드는 가짓수 1
    loop(i, n) {
        int x = coin[i];
        // j-x원을 만들 수 있다면, 여기에 x원을 추가해서 j원을 만들 수 있다.
        for (int j = x; j <= k; j++)
            DP[j] += DP[j - x];
    }
    cout << DP[k];
    return 0;
}