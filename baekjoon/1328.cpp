#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<=n;++i)
#define MOD 1000000007
#define ll long long

// DP[N][L][R] : N개의 빌딩을 왼쪽에서 볼 땐 L개,
// 오른쪽에서 볼 땐 R개가 되도록 배치하는 방법의 수
int DP[101][101][101];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, L, R; cin >> N >> L >> R;

    // basis
    DP[1][1][1] = DP[2][1][2] = DP[2][2][1] = 1;

    // 가장 높은 빌딩부터 내림차순으로 넣어본다.
    // n번째로 놓는 빌딩은 n개의 빌딩 중 가장 작으므로
    // 맨 왼쪽에 놓는다면 L은 1증가, R은 그대로이며,
    // 맨 오른쪽에 놓는다면 R은 1 증가, L은 그대로이며,
    // 빌딩 사이 어디엔가 넣는다면 L,R값은 그대로다.
    for (int n = 3; n <= N; ++n) {
        DP[n][1][n] = DP[n][n][1] = 1;
        for (int l = 1; l < n; ++l) {
            for (int r = 1; r < n; ++r) {
                if (l + r > n + 1) break;
                // 맨 왼쪽, 오른쪽에 놓는 경우
                ll tmp = DP[n - 1][l - 1][r] + DP[n - 1][l][r - 1];
                // (n-1)개의 빌딩 사이에 넣을 수 있는 자리는 (n-2)개다.
                tmp += (ll)(DP[n - 1][l][r]) * (ll)(n - 2);
                tmp %= MOD;
                DP[n][l][r] = tmp;
            }
        }
    }
    cout << DP[N][L][R];
    return 0;
}