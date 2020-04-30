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

    // DP[a][b] = a번 음과 b번음을 마지막으로 불렀을 때 최소난이도
    // DP[a][b] = DP[b][a].  순서는 중요치 않다!

    for (int i = 2; i <= N; ++i) {
        cin >> song[i];
        int val1 = gap(i, i - 1);
        DP[i][0] = DP[i - 1][0] + val1;

        for (int j = 0; j < i - 1; ++j) {
            int val2 = gap(i, j);
            DP[i][j] = min(DP[i][j], DP[i - 1][j] + val1);
            DP[i][i - 1] = min(DP[i][i - 1], DP[i - 1][j] + val2);
        }
    }

    int ans = INT_MAX;
    for (int i = 0; i < N; ++i)
        ans = min(ans, DP[N][i]);
    cout << ans;
    return 0;
}