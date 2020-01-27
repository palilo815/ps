#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define MOD 100999

int DP[2001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;

    // 1부터 i까지의 수로만 표현한다.
    for (int i = 1; i <= 2000; ++i) {
        // j를 표현 가능하면 j+i도 표현 가능
        for (int j = 2000 - i; j > 0; --j)
            DP[j + i] = (DP[j + i] + DP[j]) % MOD;
        // i = i로 나타내는 경우
        DP[i] += 1;
        DP[i] %= MOD;
    }
    while (T--) {
        int n; cin >> n;
        cout << DP[n] << '\n';
    }
    return 0;
}
