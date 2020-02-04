#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

bool DP[2][1001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    DP[0][0] = true;
    int N; cin >> N;
    loop(n, N) {
        for (int i = 1000;i >= 0;--i)
            if (DP[n % 2][i]) {
                int r = (n + 1) % 2, val = DP[n % 2][i];
                DP[r][i + 1] = true;
                DP[r][i + 5] = true;
                DP[r][i + 10] = true;
                DP[r][i + 50] = true;
            }
        memset(DP[n % 2], 0, sizeof(DP[n % 2]));
    }
    int ans = 0;
    loop(i, 1001)
        if (DP[N % 2][i]) ++ans;
    cout << ans;
    return 0;
}