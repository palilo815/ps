#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int coin[100], DP[10001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // 나중에 비교를 DP[i]+1로 하기 때문에
    // overflow방지를 위해 1을 빼주자
    loop(i, 10001)
        DP[i] = INT32_MAX - 1;

    int n, k; cin >> n >> k;
    loop(i, n) cin >> coin[i];

    loop(i, n) {
        int cost = coin[i];
        // k <= 10000이므로, 10000을 넘는 coin은 논외
        if (cost > 10000) continue;
        // 같은 동전이 또 나오는 경우
        if (DP[cost] == 1) continue;
        // cost원은 coin[i] 딱 1개로 만들 수 있다.
        DP[cost] = 1;
        // j원은 j-cost원 만드는 경우 + 1로 새로 구할 수 있다.
        for (int j = cost + 1; j <= k; ++j)
            DP[j] = min(DP[j], DP[j - cost] + 1);
    }

    if (DP[k] == INT32_MAX - 1) cout << "-1";
    else cout << DP[k];
    return 0;
}