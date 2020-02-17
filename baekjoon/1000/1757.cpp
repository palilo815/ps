// ** cubelover 풀이 참고 **
#include <bits/stdc++.h>
using namespace std;

const int max_N = 10000;

int DP[max_N + 1];
int psum[max_N + 1];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    for (int i = 1; i <= N; ++i) {
        int x; cin >> x;
        psum[i] = psum[i - 1] + x;

        // i번째에 그냥 쉬는 경우
        DP[i] = DP[i - 1];
        // j번 달리고 j번 쉬는 경우
        for (int j = 1; j <= M && 2 * j <= i; ++j)
            DP[i] = max(DP[i], DP[i - 2 * j] - psum[i - 2 * j] + psum[i - j]);
    }
    cout << DP[N];
    return 0;
}