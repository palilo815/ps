#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 16;

bool wall[max_N][max_N];
int DP[max_N][max_N][3];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) loop(j, N) cin >> wall[i][j];
    // DP[i][j][k] : [i][j]에 끝을 두고 방향은 k, [0] 가로 [1] 세로 [2] 대각
    DP[0][1][0] = 1;
    loop(i, N) loop(j, N) {
        if (j + 1 < N && !wall[i][j + 1])
            DP[i][j + 1][0] += DP[i][j][0] + DP[i][j][2];
        if (i + 1 < N && !wall[i + 1][j])
            DP[i + 1][j][1] += DP[i][j][1] + DP[i][j][2];
        if (i + 1 < N && j + 1 < N && !wall[i][j + 1] && !wall[i + 1][j] && !wall[i + 1][j + 1])
            DP[i + 1][j + 1][2] += DP[i][j][0] + DP[i][j][1] + DP[i][j][2];
    }
    int ans = 0;
    loop(i, 3) ans += DP[N - 1][N - 1][i];
    cout << ans;
    return 0;
}