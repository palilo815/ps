#include <iostream>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;
const int MOD = 1000000009;

//n을 처음으로 사용해서 num을 표현하는 가짓수
int DP[4][100003];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    DP[1][1] = DP[2][2] = DP[3][3] = 1;
    LOOP(i, 99999) LOOP(add, 3) LOOP(j, 3) {
        if (add == j) continue;
        DP[add][i + add] += DP[j][i];
        DP[add][i + add] %= MOD;
    }

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        int ans = 0;
        LOOP(i, 3) ans = (ans + DP[i][N]) % MOD;
        cout << ans << '\n';
    }
    return 0;
}