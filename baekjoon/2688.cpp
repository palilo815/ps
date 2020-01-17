#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long

// A로 시작하는 B자리 안줄수
ll DP[10][65];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // basis
    loop(i, 10) DP[i][1] = 1;

    // first로 시작하는 i-1 안줄수 앞에
    // first이하의 수인 added를 추가해서
    // i자리 안줄수를 만든다.
    for (int i = 2;i < 65; ++i)
        loop(first, 10)
        for (int added = 0; added <= first; ++added)
            DP[added][i] += DP[first][i - 1];

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        ll ans = 0;
        loop(i, 10)
            ans += DP[i][N];
        cout << ans << '\n';
    }
    return 0;
}