#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int max_N = 10;
const int max_M = 2000;

ll DP[max_N][max_M + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        memset(DP, 0, sizeof(DP));
        int N, M; cin >> N >> M;

        int bound = M / pow(2, N - 1);
        for (int i = 1; i <= bound; ++i) DP[0][i] = 1;

        // DP[idx-1][last] : idx개의 숫자 뽑고, 마지막 숫자가 last인 경우의 수
        for (int i = 0; i < N - 1; ++i) {
            int bound = M / pow(2, N - 1 - i);
            for (int j = 1; j <= bound; ++j) if (DP[i][j])
                for (int k = 2 * j; k <= M; ++k)
                    DP[i + 1][k] += DP[i][j];
        }

        ll ans = 0;
        for (int i = 1; i <= M; ++i) ans += DP[N - 1][i];
        cout << ans << '\n';
    }
    return 0;
}