#include <bits/stdc++.h>
using namespace std;

const int max_N = 2000;

int DP[max_N + 1][max_N + 1];
int song[max_N + 1];

int gap(int i, int j) { return j ? abs(song[i] - song[j]) : 0; }
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    cin >> song[1];
    
    memset(DP, 0x3f, sizeof(DP));
    DP[1][0] = DP[0][1] = 0;

    // DP[a][b] = A가 a번 음을 마지막으로 부르고 B가 b번음을 마지막으로 불렀을 때 최소난이도
    // a,b = [1,N],  0이면 아직 부르지 않음.

    for (int i = 2; i <= N; ++i) {
        cin >> song[i];
        int val1 = gap(i, i - 1);
        DP[0][i] = DP[0][i - 1] + val1;
        DP[i][0] = DP[i - 1][0] + val1;

        // DP[j][i-1] -> DP[i][i-1], DP[j][i]
        // DP[i-1][j] -> DP[i][j], DP[i-1][i]

        for (int j = 0; j < i - 1; ++j) {
            int val2 = gap(i, j);
            DP[i][j] = min(DP[i][j], DP[i - 1][j] + val1);
            DP[j][i] = min(DP[j][i], DP[j][i - 1] + val1);

            DP[i][i - 1] = min(DP[i][i - 1], DP[j][i - 1] + val2);
            DP[i - 1][i] = min(DP[i - 1][i], DP[i - 1][j] + val2);
        }
    }

    int ans = INT_MAX;
    for (int i = 0; i < N; ++i)
        ans = min({ ans,DP[N][i], DP[i][N] });
    cout << ans;
    return 0;
}