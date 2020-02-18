#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;

const int max_N = 9;
const int max_M = 100000;

// DP[N][M] : N+1개의 segment를 이용해서 만든 수 중 나머지가 M인 최댓값
ll DP[max_N][max_M];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        memset(DP, -1, sizeof(DP));
        int N, M; cin >> N >> M;
        loop(i, 10) DP[0][i % M] = i;
        DP[0][11 % M] = 11;
        loop(len, N - 1) loop(m, M) {
            if (DP[len][m] == -1) continue;
            loop(add, 10) {
                ll num = DP[len][m] * 10 + add;
                DP[len + 1][num % M] = max(DP[len + 1][num % M], num);
            }
            ll num = DP[len][m] * 100 + 11;
            DP[len + 1][num % M] = max(DP[len + 1][num % M], num);
        }
        cout << DP[N - 1][0] << '\n';
    }
    return 0;
}