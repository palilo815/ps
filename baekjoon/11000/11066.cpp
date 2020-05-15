#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;

const int max_N = 501;

int s[max_N];
int DP[max_N][max_N];
int p[max_N][max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        LOOP(i, N) {
            int x; cin >> x;
            s[i] = s[i - 1] + x;
        }
        LOOP(i, N) p[i][i] = i;

        // DP[i][j] : [i,j] 파일을 합치는 최소 비용
        // DP[i][j] = min(DP[i][k] + DP[k][j] + sum[i,j])

        LOOP(len, N) LOOP(i, N - len) {
            int j = i + len;
            DP[i][j] = INT_MAX;
            for (int k = p[i][j - 1]; k <= p[i + 1][j]; ++k)
                if (DP[i][j] > DP[i][k] + DP[k + 1][j]) {
                    DP[i][j] = DP[i][k] + DP[k + 1][j];
                    p[i][j] = k;
                }
            DP[i][j] += s[j] - s[i - 1];
        }
        cout << DP[1][N] << '\n';
    }
    return 0;
}