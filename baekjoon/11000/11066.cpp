#include <bits/stdc++.h>
#define loop(i,n) for(int i=1;i<=n;++i)
using namespace std;

const int max_N = 500;
int DP[max_N + 1][max_N + 1], psum[max_N + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        for (int i = 1;i <= N;++i) {
            int x; cin >> x;
            psum[i] = psum[i - 1] + x;
        }

        // ** DP[a][b] == [a,b]의 파일을 1개로 만드는 비용 **
        // DP[i][i+gap]을 구하는 방법:
        // tmp : [i,i+gap]의 파일을 딱 두개로 만드는 최솟값
        // psum[i+gap] - psum[i-1] : 두개의 파일을 합치는 비용
        for (int gap = 1; gap < N; ++gap) {
            for (int i = 1; i + gap <= N; ++i) {
                int tmp = INT_MAX;
                for (int j = i; j < i + gap; ++j)
                    tmp = min(tmp, DP[i][j] + DP[j + 1][i + gap]);
                DP[i][i + gap] = tmp + psum[i + gap] - psum[i - 1];
            }
        }
        cout << DP[1][N] << '\n';
    }
    return 0;
}