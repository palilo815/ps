#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_K = 199;
int DP[3][max_K + 2];
int tmp[3][max_K + 2];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    while (1) {
        int N, K; cin >> N >> K;
        if (N == 0) break;
        memset(DP, -1, sizeof(DP));
        DP[0][0] = 0;
        loop(i, N) {
            int l, r; cin >> l >> r;
            memset(tmp, -1, sizeof(tmp));
            loop(k, K + 1) {
                if (DP[0][k] != -1) {
                    tmp[0][k] = max(tmp[0][k], DP[0][k] + l + r);
                    tmp[1][k + 1] = max(tmp[1][k + 1], DP[0][k] + r);
                    tmp[2][k + 1] = max(tmp[2][k + 1], DP[0][k] + l);
                }
                if (DP[1][k] != -1) {
                    tmp[0][k] = max(tmp[0][k], DP[1][k] + l + r);
                    tmp[1][k + 1] = max(tmp[1][k + 1], DP[1][k] + r);
                }
                if (DP[2][k] != -1) {
                    tmp[0][k] = max(tmp[0][k], DP[2][k] + l + r);
                    tmp[2][k + 1] = max(tmp[2][k + 1], DP[2][k] + l);
                }
            }
            memcpy(DP, tmp, sizeof(tmp));
        }
        cout << max({ DP[0][K],DP[1][K],DP[2][K] }) << '\n';
    }
    return 0;
}