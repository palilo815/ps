#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int score[2][100000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T, N; cin >> T;
    while (T--) {
        cin >> N;
        // score[0] : 위, score[1] : 아래 스티커 점수
        loop(i, 2) loop(j, N) cin >> score[i][j];

        // DP[0] : 위, DP[1] : 아래 스티커를 사용해서 얻은 점수
        int DP[2] = {};
        loop(i, N) {
            score[0][i] += DP[1], score[1][i] += DP[0];
            // DP[n] = DP[n] : i번 column의 스티커를 쓰지 않은 경우 (점수 변화 x)
            // DP[n] = score[n][i] + DP[1 - n] : i번 column의 스티커를 쓴 경우
            DP[0] = max(DP[0], score[0][i]);
            DP[1] = max(DP[1], score[1][i]);
        }
        cout << max(DP[0], DP[1]) << '\n';
    }
}