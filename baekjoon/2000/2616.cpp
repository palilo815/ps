#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;
const int max_N = 50000;

int psum[max_N + 1], DP[3][max_N + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    LOOP(i, N) {
        int x; cin >> x;
        psum[i] = psum[i - 1] + x;
    }
    int K; cin >> K;
    // 기차 한 개만 사용
    for (int i = K; i <= N; ++i)
        DP[0][i] = max(DP[0][i - 1], psum[i] - psum[i - K]);
    // 두 개만 사용
    for (int i = 2 * K; i <= N; ++i)
        DP[1][i] = max(DP[1][i - 1], DP[0][i - K] + psum[i] - psum[i - K]);
    // 세 개 전부 사용
    for (int i = 3 * K; i <= N; ++i)
        DP[2][i] = max(DP[2][i - 1], DP[1][i - K] + psum[i] - psum[i - K]);
    cout << DP[2][N];
    return 0;
}